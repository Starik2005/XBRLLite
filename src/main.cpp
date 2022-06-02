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
    char buf[256]{0};
    char tagName[10000]{0};
    char data[10000]{0};
    int rd,ti,di,rd0 = {0};
    bool otag,oname = 0;
    char x;

    while(rd = zip_fread(fl, buf, 256))
    {
        rd0 = 0;
        while(rd--){
            x = buf[rd0++];
            if (otag)
                if (x=='>'||x==' '||x=='/') {
                    otag = 0;
                    tagName[ti++] = 0;
                    if (ti>1)
                        std::cout << tagName;
                    ti = 0;
                    if(x=='>'){oname=1; continue;}
                } else tagName[ti++] = x;
            if(x=='<') {
                    otag = 1;
                    if (oname) {
                        oname = 0;
                        data[di++] = 0;
                        if (di>1)
                            std::cout  << " = \"" << data << "\"\n";
                        di = 0;
                    }
                }
            if(oname) data[di++] = x;
        }
    }

    zip_close(zipper);

    std::cout << '\n';

    std::cout << num << '\n';
 return 0; 
}

