#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main()
{

//print entire line
    std::ifstream filestat("/proc/stat");
    std::string line;

    while(std::getline(filestat,line))
    {
        std::cout<<line<<std::endl;
    }
    //
    struct data_type
    {
        data_type(int i,string description);
        int position;
        string description;
    };
    int counter=-1;

    vector<data_type> dataVec;
    dataVec.push_back(data_type(1,"Time spent in user mode: "));
    dataVec.push_back(data_type(3,"Time spent in system mode: "));
    dataVec.push_back(data_type(6,"Time servicing interrupts: "));
    while(std::getline(filestat,line))
    {
        if(line.at(0)=='c'&&line.at(1)=='p'&&line.at(2)=='u')
        {
            if(counter==-1)
            {
                cout<<"cpu: "<<endl;
                counter++;
            }
            else
            {
                cout<<"cpu"<<counter<<": "<<endl;
                counter++;
            }
            for(data_type j: dataVec)
            {
                string output=line;
                int count_start=0;
                for(int k=0;k<j.position;k++)
                {
                  while(output.at(count_start)!=' ')
                  {
                     count_start++;
                  }
                }
                int count_end=count_start+1;
                while(output.at(count_end)!=' ')
                {
                    count_end++;
                }
                output=output.substr(count_start,count_end);
                cout<<j.description<<output<<endl;

            }

            }
        else
        {
            break;
            /*
            for(data_type j: dataVec)
            {
                string output=line;
                int count_start=0;
                for(int k=0;k<j.position-1;k++)
                {
                    while(output.at(count_start)!=' ')
                    {
                        count_start++;
                    }
                }
                int count_end=count_start+1;
                while(output.at(count_end)!=' ')
                {
                    count_end++;
                }
                output=output.substr(count_start,count_end);
                cout<<j.description<<output<<endl;


            }
             */
        }
    }


    std::getline(filestat,line);
    std::cout<<line<<std::endl;

//print specific number (ignore string and go to the forth number)
    unsigned n;
    if(std::ifstream("/proc/stat").ignore(3) >> n)
    {
// use n here...
        cout << "Time spent in user mode: " << n << endl;
    }
    if(std::ifstream("/proc/stat").ignore(3) >> n >> n >> n)
    {
// use n here...
        cout << "Time spent in system mode: " << n << endl;
    }
    if(std::ifstream("/proc/stat").ignore(3) >> n >> n >> n >> n >> n >> n)
    {
// use n here...
        cout << "Time servicing interrupts: " << n << endl;
    }


    return 0;
}


