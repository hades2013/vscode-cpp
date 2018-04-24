#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <regex>
 
int main()
{
   std::string text = "Quick brown fox.";
   // 记号化（非匹配碎片）
   // 注意仅匹配二次 regex ：在获得第三值时迭代器为后缀迭代器。
   std::regex ws_re("\\s+"); // 空白符
   std::copy( std::sregex_token_iterator(text.begin(), text.end(), ws_re, -1),
              std::sregex_token_iterator(),
              std::ostream_iterator<std::string>(std::cout, "\n"));
 
   // 迭代首个子匹配
   std::string html = "<p><a href=\"http://google.com\">google</a> "
                      "< a HREF =\"http://cppreference.com\">cppreference</a>\n</p>";
   std::regex url_re("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"", std::regex::icase);
   std::copy( std::sregex_token_iterator(html.begin(), html.end(), url_re, 1),
              std::sregex_token_iterator(),
              std::ostream_iterator<std::string>(std::cout, "\n"));
}