namespace lua_juce {
auto juce_IPAddress(sol::table& state) -> void
{
    // clang-format off
    auto ip = state.new_usertype<juce::IPAddress>("IPAddress",
        sol::constructors<
            juce::IPAddress(),
            juce::IPAddress(juce::uint32),
            juce::IPAddress(juce::String const&),
            juce::IPAddress(juce::uint8*, bool),
            juce::IPAddress(juce::uint16*),
            juce::IPAddress(juce::uint8, juce::uint8, juce::uint8, juce::uint8),
            juce::IPAddress(juce::uint16, juce::uint16, juce::uint16, juce::uint16, juce::uint16, juce::uint16, juce::uint16, juce::uint16)
        >()
    );
    // clang-format on

    ip["isNull"]   = LUA_JUCE_C_CALL(&juce::IPAddress::isNull);
    ip["toString"] = LUA_JUCE_C_CALL(&juce::IPAddress::toString);
    ip["compare"]  = LUA_JUCE_C_CALL(&juce::IPAddress::compare);

    ip["any"]                            = LUA_JUCE_C_CALL(&juce::IPAddress::any);
    ip["broadcast"]                      = LUA_JUCE_C_CALL(&juce::IPAddress::broadcast);
    ip["findAllAddresses"]               = LUA_JUCE_C_CALL(&juce::IPAddress::findAllAddresses);
    ip["getAllAddresses"]                = LUA_JUCE_C_CALL(&juce::IPAddress::getAllAddresses);
    ip["getLocalAddress"]                = LUA_JUCE_C_CALL(&juce::IPAddress::getLocalAddress);
    ip["getFormattedAddress"]            = LUA_JUCE_C_CALL(&juce::IPAddress::getFormattedAddress);
    ip["isIPv4MappedAddress"]            = LUA_JUCE_C_CALL(&juce::IPAddress::isIPv4MappedAddress);
    ip["convertIPv4MappedAddressToIPv4"] = LUA_JUCE_C_CALL(&juce::IPAddress::convertIPv4MappedAddressToIPv4);
    ip["convertIPv4AddressToIPv4Mapped"] = LUA_JUCE_C_CALL(&juce::IPAddress::convertIPv4AddressToIPv4Mapped);
    ip["getInterfaceBroadcastAddress"]   = LUA_JUCE_C_CALL(&juce::IPAddress::getInterfaceBroadcastAddress);

    ip["address"] = &juce::IPAddress::address;
    ip["isIPv6"]  = &juce::IPAddress::isIPv6;
}
} // namespace lua_juce
