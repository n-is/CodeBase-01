#include "/usr/include/externals/catch.hpp"
#include "../utils/Error.h"

TEST_CASE("Error Handling functions are Checked", "[Error]")
{
        Error e1 = Error::NameError;
        REQUIRE(raise(e1) == -1);
        Error e2 = Error::TypeError;
        REQUIRE(raise(e2) == -1);
        Error e3 = Error::TokenError;
        REQUIRE(raise(e3) == -1);
        Error e4 = Error::SyntaxError;
        REQUIRE(raise(e4) == -1);
}
