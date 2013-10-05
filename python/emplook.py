# Comments Ldap directory search using python_ldap
import os
import sys
import ldap

#debuggin options if required 
ldapmodule_trace_level = 0
ldapmodule_trace_file = ''

basedn = "OU=Employees,OU=Domain Users,DC=domain,DC=com"
#basedn = ""
opt = str(sys.argv)
opt_len = len(sys.argv)
result_set = []

# List of guessables 
engineer     = "ENGINEER"
software     = "SOFTWARE"
architect    = "ARCHITECT"
manager      = "MANAGER"
developement = "DEVELOPMENT"
consultant   = "CONSULTANT"

# No Pun inteneded
def changeTitle(act_title):
    mtitle = act_title.replace("ENGINEERING","ENGINE-NEARING").replace(engineer,"ENDANGERER").replace(software,"SOFTAGE")
    mtitle = mtitle.replace(manager,"MAN-AGER")
    mtitle = mtitle.replace(architect,"BUS-CONDUCTOR")
    mtitle = mtitle.replace(developement,"D-MENTAL")
    return mtitle + "ENGINEER"

if(opt_len >= 3): 
    fname = sys.argv[1]
    sname = sys.argv[2]
    filter = "(&(givenName=" + fname + "*)(sn=" + sname +"*))"
else:
    fname = sys.argv[1]
    filter = "(givenName=" + fname + "*)"

# change these for your domain pswd...
# connect to ldap Move password to appropriate place
con = ldap.initialize('ldap://ldap_directory.com:3268')
con.protocol_version=ldap.VERSION3
con.bind_s("user@domain.com", "pswd", ldap.AUTH_SIMPLE);

results = con.search_s(basedn,ldap.SCOPE_SUBTREE,filter)
result_set.append(results)
result_len = len(results) 

# Result Set Here
if(result_len > 1):
    for i in range(result_len):
        if (i <= 0):
            for entry in result_set[i]:
                name = entry[1]['description'][0]
                mail = entry[1]['mail'][0]
                title = entry[1]['title'][0]
                title = changeTitle(title)
                print '| ',name ,'| ', mail,' | ', title
else:
    for i in range(len(results)):
        for entry in result_set[i]:
            name = entry[1]['description'][0]
            mail = entry[1]['mail'][0]
            title = entry[1]['title'][0]
            title = changeTitle(title)
            print '| ',name ,'| ', mail,' | ', title
n
