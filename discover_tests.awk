BEGIN { FS = "[ \t()]+" }
/TEST_CASE/ { print "void TestCase_" $2 "(TestCounter*);" > "all_tests.h"; print "TestCase_" $2 "," > "all_tests.inc" }
