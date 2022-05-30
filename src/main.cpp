//////////////////////////////////////*
* THIS CODE FOR READING TAXONOMY ONLY *
*//////////////////////////////////////

#include <iostream>
#include <zip.h>
#include <unordered_set>
#include <string>

std::unordered_set<std::string> files;

int main()
{
    int errorp;
    zip_t *zipper = zip_open("final_5.zip", 16, &errorp);
    int num = zip_get_num_files(zipper);
    zip_flags_t zf;
    for(int i = 0; i<num; i++)
        files.insert(std::string(zip_get_name(zipper, i, zf)));

    zip_file_t * fl = zip_fopen(zipper, "final_5/META-INF/entry_point.xml", zf);
    char* buf = new char[10000]{0};
    int rd = {0};
    int b = {0};
    bool otag = 0;
    bool oname = 0;
    while(rd = zip_fread(fl, buf, 10000))
    {
       b = 0;
       for(; rd>0; rd--){
             if (otag)
                 if (buf[b]=='>'||buf[b]==' '||buf[b]=='/') {
                     otag = 0;
                     t = 0;
                     if(buf[b]=='>') {oname=1; b++; std::cout << " DATA: "; continue; }
                     } else std::cout << buf[b];
             if(buf[b]=='<') {
                     otag = 1;
                     std::cout << '\n' << "TAG: ";
                     if (oname) {
                         oname = 0;
                         d = 0;
                     }
                 }
            if(oname)std::cout << buf[b];
            b++;
        }
    }

    zip_close(zipper);

    std::cout << '\n';
    std::cout << num << '\n';

 return 0;
}
