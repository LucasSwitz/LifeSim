import os



def make():
    includes = ""
    clazz = """
    class Statics
    {
    public:
        static void Init()
        {     
"""

    for dirpath,_, filenames in os.walk("../src/game_objects/actor/goal/"):
        for f in filenames:
            if ": public Goal" in open(os.path.join(dirpath,f)).read():
                includes += '#include "' + os.path.abspath(os.path.join(dirpath,f)) + '"\n'
                clazz += "\t "+f[0:-2] + "::Instance(); \n"

    for dirpath,_, filenames in os.walk("../src/game_objects/actor/actions/"):
        for f in filenames:
            if ": public Action" in open(os.path.join(dirpath,f)).read():
                includes += '#include "' + os.path.abspath(os.path.join(dirpath,f)) + '"\n'
                clazz += "\t new " + f[:-2] + "(); \n"

    clazz += "} \n };"
    return includes + clazz

print("Building Statics....")
f = open("../src/utils/Statics.h",'w')
f.write(make())
f.close()
print ("Built Statics!")