#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct data_type
    {
        data_type();
        data_type(int i,string description);
        int position;
        string description;
    };

data_type::data_type()
{
    position=0;
    description="";
}
data_type::data_type(int i,string description)
{
    this->position=i;
    this->description=description;
}

int main()
{
    std::ifstream filestat("/proc/stat");
    std::string line;
    int counter=-1;

    vector<data_type> dataVec;
    data_type new_data;
    new_data = data_type(1, "Time spent in user mode: ");
    dataVec.push_back(new_data);
    new_data =  data_type(3,"Time spent in system mode: ");
    dataVec.push_back(new_data);
    new_data = data_type(6,"Time servicing interrupts: ");
    dataVec.push_back(new_data);

    while(std::getline(filestat,line))
    {
        if(line.at(0)=='c'&&line.at(1)=='p'&&line.at(2)=='u') //cpu details
        {
            if(counter==-1)//printing the currect cpu number
            {
                cout<<"cpu: "<<endl;
                counter++;
            }
            else
            {
                cout<<"cpu"<<counter<<": "<<endl;
                counter++;
            }

            for(data_type j: dataVec)//we print all the data we want for each cpu
            {
                string temp_line=line,token;
                int count_start=0;

                count_start=temp_line.find(' ');
                count_start++;

                for(int i=0;i<j.position;i++)
                {

                        while(temp_line.at(count_start)!=' ')
                        {
                            count_start++;
                        }
                        count_start++;

                }//now we know where the relevant number begins
                int count_end=count_start;
                while(temp_line.at(count_end)!=' ')
                {
                    count_end++;
                }
                count_end--;
                //now we know where the relevant number ends
                int sizeOfToken=count_end-count_start+1;
                token=temp_line.substr(count_start,sizeOfToken);
                cout<<j.description<<token<<endl;//printing the relevant number


            }

        }
        else
        {
            break;

        }
    }

    return 0;
}


