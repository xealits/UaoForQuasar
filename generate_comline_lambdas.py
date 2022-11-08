from bs4 import BeautifulSoup as bs

filename = "../Design/Design.xml"
device_class = "LpGBT" # "AMAC"

content = []

# Read the XML file
with open(filename, "r") as file:
    # Read each line in the file, readlines() returns a list of lines
    content = file.readlines()
    # Combine the lines in the list into a string
    content = "".join(content)
    bs_content = bs(content, features="xml")

#result = bs_content.find_all("d:class")

design_dev = bs_content.find("d:class", attrs={"name" : device_class})

dev_cvs = [(cv.attrs['name'], cv.attrs['dataType']) for cv in design_dev.find_all("d:cachevariable")]

opc_datatype_conversion = {
	"OpcUa_Boolean" : ('b'   , 'b = other.b;', ''),
	"OpcUa_Double"  : ('d'   , 'd = other.d;', ''),
	"OpcUa_Int16"   : ('i16' , 'i16 = other.i16;', ''),
	"OpcUa_Int32"   : ('i32' , 'i32 = other.i32;', ''),
	"OpcUa_Int64"   : ('i64' , 'i64 = other.i64;', ''),
	"UaString"      : ('s'   , 'new(&s) auto(other.s);', 'new(&s) std::string();'),
}

all_opc_data_types_string = '\t'.join('%s %s;\n' % (i[0], i[1][0]) for i in opc_datatype_conversion.items())
all_opc_data_copying = ' '.join(v[1] for v in opc_datatype_conversion.values() if v[1])
all_opc_data_inits   = ' '.join(v[2] for v in opc_datatype_conversion.values() if v[2])

# generate the std::map code
c_definitions = f'''
#include <map>
#include <string>
#include <functional>

//dataType="OpcUa_Boolean"
//dataType="OpcUa_Double"
//dataType="OpcUa_Int16"
//dataType="OpcUa_Int32"
//dataType="OpcUa_Int64"
//dataType="UaString"

union OpcData {{
	{all_opc_data_types_string}

	OpcData() {{ {all_opc_data_inits} }}
	OpcData(const OpcData& other) {{ {all_opc_data_copying} }}
	~OpcData() {{}}
}};
'''

c_map_lambdas_cv_pairs = []
c_map_types_pairs      = []
for cv_name, cv_type in dev_cvs:
    func = f'[](UaoClient::{device_class}& dev) -> union OpcData {{union OpcData res; res.{opc_datatype_conversion[cv_type][0]} = dev.read{cv_name}(); return res;}}'
    c_map_lambdas_cv_pairs.append('  {"%s", %s}' % (cv_name, func))

    c_map_types_pairs.append('  {"%s", "%s"}' % (cv_name, cv_type))


c_map_lambdas = f'''
std::map<std::string, std::function<OpcData(UaoClient::{device_class}&)>> _comline_lambdas_{device_class} = {{
'''
c_map_lambdas += ',\n'.join(c_map_lambdas_cv_pairs)
c_map_lambdas += '\n};'

c_map_types = f'''
std::map<std::string, std::string> _comline_types_{device_class} = {{
'''
c_map_types += ',\n'.join(c_map_types_pairs)
c_map_types += '\n};'

print(c_definitions)
print(c_map_lambdas)
print(c_map_types)

