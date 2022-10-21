from bs4 import BeautifulSoup as bs

filename = "../Design/Design.xml"
device_class = "AMAC"

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

dev_cvs = [cv.attrs['name'] for cv in design_dev.find_all("d:cachevariable")]

# generate the std::map code
header = f'''
#include <map>

std::map _comline_lambdas_{device_class} = {{
'''

footer = '''}
'''

cv_pairs = []
for cv in dev_cvs:
    func = f'[](UaoClient::{device_class}& dev) {{return dev.read{cv}();}}'
    cv_pairs.append('  {"%s", %s}' % (cv, func))

print(header)
print(',\n'.join(cv_pairs))
print(footer)
