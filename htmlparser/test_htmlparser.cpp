#include <ztest/ztest.h>
#include "htmlparser.h"

#pragma warning(disable: 4996)

Z_BEGIN_TEST_CLASS(HtmlParser)
    Z_DECLARE_TEST_CASE(GetAHref)
Z_END_TEST_CLASS()

Z_DEFINE_TEST_OBJECT(HtmlParser, tester);

class ParseATag : public EventHandler
{
public:

    explicit ParseATag(const char * tag) :
        EventHandler(tag)
    {}

    bool OnEvent(const char * begin_pos, size_t len, 
        const char *& cur_pos)
    {
        const char * pos = strchr(cur_pos, '>');
        if (pos != NULL)
        {
            std::string content(cur_pos, pos - cur_pos);
            printf("%s\n", content.c_str());
        
            cur_pos = pos + 1;
            return true;
        }
        return false;
    }
};

Z_DEFINE_TEST_CASE(HtmlParser, tester, GetAHref)
{
    static const int s_max_page_len = (1<<20);
    FILE * fp = fopen("input1.html", "r");
    char buffer[s_max_page_len] = {0};
    size_t len = 0;
    size_t num = 0;

    while ((num = fread(buffer + len, 1, 1024, fp)) > 0)
    {
        len += num;
    }

    HtmlParser parser(buffer, len);
}

int main()
{
    Z_RUN_ALL_TESTCASES(tester);
}
