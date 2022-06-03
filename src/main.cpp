#include <iostream>
#include <zip.h>
#include <unordered_set>
#include <string>
#include <bits/stdc++.h>

struct Xbr {
    std::string NFOTypeRus, ReportPeriodType, PathToXsd, ReportTypeRus;
    Xbr(std::string a,std::string b,std::string c,std::string d)
    {
        NFOTypeRus = a;
        ReportPeriodType = b;
        PathToXsd = c;
        ReportTypeRus = d;
    }

    bool operator==(const Xbr& p) const
    {
        return PathToXsd == p.PathToXsd && ReportTypeRus == p.ReportTypeRus;
    }    
};

class MyHashFunction {
public:

    size_t operator()(const Xbr& p) const
    {
        return (std::hash<std::string>()(p.PathToXsd));
    }

};

std::unordered_set<Xbr, MyHashFunction> ep;

int main()
{
    int errorp;
    zip_t *zipper = zip_open("final_5.zip", 16, &errorp);

    int num = zip_get_num_files(zipper);

    zip_flags_t zf;
    zip_file_t * fl = zip_fopen(zipper, "final_5/META-INF/entry_point.xml", zf);

    char buf[256]{0};
    char tagName[10000]{0};
    char data[10000]{0};
    int rd,ti,di,rd0 = {0};
    bool otag,oname = 0;
    char x;
    bool newxbr = 0;

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
                        if(tagName == "NFOType")
                            newxbr = 1;
                        //std::cout << tagName;
                    ti = 0;
                    if(x=='>'){oname=1; continue;}
                } else tagName[ti++] = x;
            if(x=='<') {
                    otag = 1;
                    if (oname) {
                        oname = 0;
                        data[di++] = 0;
                        if (di>1)
                            if (!strcmp(tagName, "ReportTypeRus"))
                            {
                                Xbr x1(std::string(tagName), std::string(data), "2", "3");
                                ep.insert(x1);
                                //std::cout  << " = \"" << data << "\"\n";
                            }
                                
                            
                        di = 0;
                    }
                }
            if(oname) data[di++] = x;
        }
    }

    for(auto i: ep)
    {
        std::cout << i.NFOTypeRus << " = " << i.ReportPeriodType << std::endl;
    }
    zip_close(zipper);

    std::cout << '\n';

    std::cout << num << '\n';
 return 0; 
}

