import ROOT
import json

ROOT.gInterpreter.LoadMacro('./root-scripts/createFromJsonString.C')

def create_directly(className : str, args : list):
    return ROOT.createFromJsonString(json.dumps({"class" : className, "args" : args}))
