namespace lua_juce {
auto juce_BigInteger(sol::table& state) -> void
{
    // clang-format off
    auto bigInt = state.new_usertype<juce::BigInteger>("BigInteger",
        sol::constructors<
            juce::BigInteger(),
            juce::BigInteger(juce::uint32),
            juce::BigInteger(juce::int32),
            juce::BigInteger(juce::int64)
        >()
    );
    bigInt.set_function("setBit", sol::overload(
            static_cast<juce::BigInteger& (juce::BigInteger::*)(int)>(&juce::BigInteger::setBit),
            static_cast<juce::BigInteger& (juce::BigInteger::*)(int, bool)>(&juce::BigInteger::setBit)
        )
    );
    // clang-format on
    bigInt["swapWith"]                  = LUA_JUCE_C_CALL(&juce::BigInteger::swapWith);
    bigInt["isZero"]                    = LUA_JUCE_C_CALL(&juce::BigInteger::isZero);
    bigInt["isOne"]                     = LUA_JUCE_C_CALL(&juce::BigInteger::isOne);
    bigInt["toInteger"]                 = LUA_JUCE_C_CALL(&juce::BigInteger::toInteger);
    bigInt["toInt64"]                   = LUA_JUCE_C_CALL(&juce::BigInteger::toInt64);
    bigInt["clear"]                     = LUA_JUCE_C_CALL(&juce::BigInteger::clear);
    bigInt["clearBit"]                  = LUA_JUCE_C_CALL(&juce::BigInteger::clearBit);
    bigInt["setRange"]                  = LUA_JUCE_C_CALL(&juce::BigInteger::setRange);
    bigInt["insertBit"]                 = LUA_JUCE_C_CALL(&juce::BigInteger::insertBit);
    bigInt["getBitRange"]               = LUA_JUCE_C_CALL(&juce::BigInteger::getBitRange);
    bigInt["getBitRangeAsInt"]          = LUA_JUCE_C_CALL(&juce::BigInteger::getBitRangeAsInt);
    bigInt["setBitRangeAsInt"]          = LUA_JUCE_C_CALL(&juce::BigInteger::setBitRangeAsInt);
    bigInt["shiftBits"]                 = LUA_JUCE_C_CALL(&juce::BigInteger::shiftBits);
    bigInt["countNumberOfSetBits"]      = LUA_JUCE_C_CALL(&juce::BigInteger::countNumberOfSetBits);
    bigInt["findNextSetBit"]            = LUA_JUCE_C_CALL(&juce::BigInteger::findNextSetBit);
    bigInt["findNextClearBit"]          = LUA_JUCE_C_CALL(&juce::BigInteger::findNextClearBit);
    bigInt["getHighestBit"]             = LUA_JUCE_C_CALL(&juce::BigInteger::getHighestBit);
    bigInt["isNegative"]                = LUA_JUCE_C_CALL(&juce::BigInteger::isNegative);
    bigInt["setNegative"]               = LUA_JUCE_C_CALL(&juce::BigInteger::setNegative);
    bigInt["negate"]                    = LUA_JUCE_C_CALL(&juce::BigInteger::negate);
    bigInt["compare"]                   = LUA_JUCE_C_CALL(&juce::BigInteger::compare);
    bigInt["compareAbsolute"]           = LUA_JUCE_C_CALL(&juce::BigInteger::compareAbsolute);
    bigInt["divideBy"]                  = LUA_JUCE_C_CALL(&juce::BigInteger::divideBy);
    bigInt["findGreatestCommonDivisor"] = LUA_JUCE_C_CALL(&juce::BigInteger::findGreatestCommonDivisor);
    bigInt["exponentModulo"]            = LUA_JUCE_C_CALL(&juce::BigInteger::exponentModulo);
    bigInt["inverseModulo"]             = LUA_JUCE_C_CALL(&juce::BigInteger::inverseModulo);
    bigInt["montgomeryMultiplication"]  = LUA_JUCE_C_CALL(&juce::BigInteger::montgomeryMultiplication);
    bigInt["extendedEuclidean"]         = LUA_JUCE_C_CALL(&juce::BigInteger::extendedEuclidean);
    bigInt["toString"]                  = LUA_JUCE_C_CALL(&juce::BigInteger::toString);
    bigInt["parseString"]               = LUA_JUCE_C_CALL(&juce::BigInteger::parseString);
    bigInt["toMemoryBlock"]             = LUA_JUCE_C_CALL(&juce::BigInteger::toMemoryBlock);
    bigInt["loadFromMemoryBlock"]       = LUA_JUCE_C_CALL(&juce::BigInteger::loadFromMemoryBlock);
}
} // namespace lua_juce
