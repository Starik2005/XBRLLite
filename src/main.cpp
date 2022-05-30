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
    char* tagName = new char[10000]{0};
    char* data = new char[10000]{0};
    int rd = {0};
    int t = {0};
    int d = {0};
    int b = {0};
    bool otag = 0;
    bool oname = 0;
    while(rd = zip_fread(fl, buf, 10000))
    {
       b = 0;
       for(; rd>0; rd--){
           //std::cout << buf[b++];
             if (otag)
                 if (buf[b]=='>'||buf[b]==' '||buf[b]=='/') {
                     otag = 0;
                     t = 0;
                     if(buf[b]=='>') {oname=1; b++; std::cout << " DATA: "; continue; }
                     } else std::cout << buf[b];//tagName[t++] = buf[b];
             if(buf[b]=='<') {
                     otag = 1;
                     std::cout << '\n' << "TAG: ";
                     if (oname) {
                         oname = 0;
                         //data[d] = 0;
                         //std::cout << data << ": DATA\n";
                         d = 0;
                     }
                 }
            if(oname)std::cout << buf[b];   //data[d++] = buf[b];

            //if(oname)data[d++] = buf[b];
            b++;
        }
    }
    //if(t!=tagName)std::cout << tagName;

    zip_close(zipper);

    std::cout << '\n';

    std::cout << num << '\n';
    // for(auto i: files)
    //    std::cout << i << '\n';

 return 0;
}
