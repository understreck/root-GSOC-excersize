using json = nlohmann::json;

std::string
convert(json const& value) {
    using value_t = json::value_t;

    auto string = std::string{};

    switch(value.type()) {
        case value_t::array: {
            if(value.empty()) {
                string += "{}";
                break;
            }

            string += '{';
            for(int i = 0; i < value.size() - 1; i++) {
                string += convert(value[i]) + ", ";
            }
            string += convert(value[value.size() - 1]) + '}';
        } break;

        case value_t::string:
        [[fallthrough]];
        case value_t::boolean:
        [[fallthrough]];
        case value_t::number_integer:
        [[fallthrough]];
        case value_t::number_unsigned:
        [[fallthrough]];
        case value_t::number_float: {
            string += value.dump();
        } break;


        //TODO: figure out if these are valid is valid here
        //And if not implement error handling
        case value_t::object: {} break;
        case value_t::binary: {} break;
        case value_t::discarded: {} break;
        case value_t::null: {} break;
    
        //TODO: error management
        default: {} //should never get here
    }

    return string;
}

std::unique_ptr<TObject>
//auto
createFromJsonString(std::string const &jsonStr) {
    auto jsonObject = json::parse(jsonStr);
    
    auto interpString = 
        std::string{"new "} +
        jsonObject.at("class").get<std::string>();

    interpString += convert(jsonObject.at("args")) + ';';

    //return args;
    //return interpString;
    return std::unique_ptr<TObject>{
        reinterpret_cast<TObject *>(
            gInterpreter->ProcessLine(interpString.data()))
    };
}
