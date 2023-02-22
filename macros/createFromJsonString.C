using json = nlohmann::json;

/* std::string jsonToConstructorArguments(nlohmann::json const&)
 * Recursively constructs C++ constructor argument from a subset
 * of valid json objects and types
 */
std::string
jsonToConstructorArguments(json const& value) {
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
                string += jsonToConstructorArguments(value[i]) + ", ";
            }
            string += jsonToConstructorArguments(value[value.size() - 1]) + '}';
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


        case value_t::object:
        [[fallthrough]];
        case value_t::binary:
        [[fallthrough]];
        case value_t::discarded:
        [[fallthrough]];
        case value_t::null: {
            throw std::invalid_argument{
                "Invalid nlohmann::json::value_t type enum: " +
                std::string{value.type_name()}
            };
        } break;

        default: {
            throw std::invalid_argument{
                "Out of range nlohmann::json::value_t type enum: " +
                std::string{value.type_name()} + '\n' +
                "This should not be able to happen and is probably an error in nlohmann::json"
            };
        }
    }

    return string;
}

std::unique_ptr<TObject>
createFromJsonString(std::string const &jsonStr) {
    auto jsonObject = json::parse(jsonStr);

    auto interpString = 
        std::string{"new "} +
        jsonObject.at("class").get<std::string>();

    interpString += jsonToConstructorArguments(jsonObject.at("args")) + ';';

    return std::unique_ptr<TObject>{
        reinterpret_cast<TObject *>(
            gInterpreter->ProcessLine(interpString.data()))
    };
}
