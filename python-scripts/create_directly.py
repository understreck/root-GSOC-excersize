import ROOT
import json

ROOT.gInterpreter.LoadMacro('./root-scripts/MyClass.C')
ROOT.gInterpreter.LoadMacro('./root-scripts/createFromJsonString.C')

def create_directly(className : str, args : list):
    return ROOT.createFromJsonString(json.dumps({"class" : className, "args" : args}))

obj_1 = create_directly("MyClass", ["first", "The First Instance", 1])
obj_1.Print()
