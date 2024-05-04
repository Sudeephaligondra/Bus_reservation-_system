#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
static int p = 0;
class Bus
{
    char busn[5], driver[10], arrival[5], depart[5], from[10], to[10], seat[8][4][10];
public:
    void install();
    void allotment();
    void empty();
    void show();
    void avail();
    void position(int i);
};

Bus bus[10];

void vline(char ch)
{
    for (int i = 80; i > 0; i--)
        cout << ch;
}

void Bus::install()
{
    cout << "Enter bus no: ";
    cin >> bus[p].busn;
    cout << "\nEnter Driver's name: ";
    cin >> bus[p].driver;
    cout << "\nArrival time: ";
    cin >> bus[p].arrival;
    cout << "\nDeparture: ";
    cin >> bus[p].depart;
    cout << "\nFrom: \t\t\t";
    cin >> bus[p].from;
    cout << "\nTo: \t\t\t";
    cin >> bus[p].to;
    bus[p].empty();

    // Save data to file
    FILE* file = fopen("data.txt", "a");
    if (file != NULL)
    {
        fwrite(&bus[p], sizeof(Bus), 1, file);
        fclose(file);
    }

    p++;
}

void Bus::allotment()
{
    int seat;
    char number[5];

    top:
    cout << "Bus no: ";
    cin >> number;

    FILE* file = fopen("data.txt", "r+");
    if (file != NULL)
    {
        while (fread(&bus[p], sizeof(Bus), 1, file) == 1)
        {
            if (strcmp(bus[p].busn, number) == 0)
                break;
        }
        fclose(file);
    }
    if (file == NULL || feof(file))
    {
        cout << "Enter correct bus no.\n";
        goto top;
    }
    while (!feof(file))
    {
        cout << "\nSeat Number: ";
        cin >> seat;
        if (seat > 32)
        {
            cout << "\nThere are only 32 seats available in this bus.";
        }
        else
        {
            if (strcmp(bus[p].seat[seat / 4][(seat % 4) - 1], "Empty") == 0)
            {
                cout << "Enter passenger's name: ";
                cin >> bus[p].seat[seat / 4][(seat % 4) - 1];
                break;
            }
            else
            {
                cout << "The seat no. is already reserved.\n";
            }
        }
    }

    file = fopen("data.txt", "r+");
    if (file != NULL)
    {
        fseek(file, ftell(file) - sizeof(Bus), SEEK_SET);
        fwrite(&bus[p], sizeof(Bus), 1, file);
        fclose(file);
    }
}

void Bus::empty()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            strcpy(bus[p].seat[i][j], "Empty");
        }
    }
}

void Bus::show()
{
    int n;
    char number[5];
    cout << "Enter bus no: ";
    cin >> number;

    FILE* file = fopen("data.txt", "r");
    if (file != NULL)
    {
        while (fread(&bus[p], sizeof(Bus), 1, file) == 1)
        {
            if (strcmp(bus[p].busn, number) == 0)
                break;
        }
        fclose(file);
    }

    if (file == NULL || feof(file))
    {
        cout << "Enter correct bus no: ";
        return;
    }

    vline('*');
    cout << "Bus no: \t" << bus[n].busn
         << "\nDriver: \t" << bus[n].driver << "\t\tArrival time: \t"
         << bus[n].arrival << "\tDeparture time:" << bus[n].depart
         << "\nFrom: \t\t" << bus[n].from << "\t\tTo: \t\t"
         << bus[n].to << "\n";
    vline('*');
    bus[0].position(n);

    int a = 1;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            a++;
            if (strcmp(bus[n].seat[i][j], "Empty") != 0)
            {
                cout << "\nThe seat no " << (a - 1) << " is reserved for " << bus[n].seat[i][j] << ".";
            }
        }
    }
}

void Bus::position(int l)
{
    int s = 0;
    p = 0;
    for (int i = 0; i < 8; i++)
    {
        cout << "\n";
        for (int j = 0; j < 4; j++)
        {
            s++;
            if (strcmp(bus[l].seat[i][j], "Empty") == 0)
            {
                cout.width(5);
                cout.fill(' ');
                cout << s << ".";
                cout.width(10);
                cout.fill(' ');
                cout << bus[l].seat[i][j];
                p++;
            }
            else
            {
                cout.width(5);
                cout.fill(' ');
                cout << s << ".";
                cout.width(10);
                cout.fill(' ');
                cout << bus[l].seat[i][j];
            }
        }
    }
    cout << "\n\nThere are " << p << " seats empty in Bus No: " << bus[l].busn;
}

void Bus::avail()
{
    FILE* file = fopen("data.txt", "r");
    if (file != NULL)
    {
        while (fread(&bus[p], sizeof(Bus), 1, file) == 1)
        {
            vline('*');
            cout << "Bus no: \t" << bus[p].busn << "\nDriver: \t" << bus[p].driver
                 << "\t\tArrival time: \t" << bus[p].arrival << "\tDeparture Time: \t"
                 << bus[p].depart << "\nFrom: \t\t" << bus[p].from << "\t\tTo: \t\t\t"
                 << bus[p].to << "\n";
            vline('*');
            vline('_');
        }
        fclose(file);
    }
}

int main()
{
    FILE* file = fopen("data.txt", "a+");

system("cls");

int w;

while(1)

{

    //system("cls");

  cout<<"\n\n\n\n\n";

  cout<<"\t\t\t1.Install\n\t\t\t"

  <<"2.Reservation\n\t\t\t"

  <<"3.Show\n\t\t\t"

  <<"4.Buses Available. \n\t\t\t"

  <<"5.Exit";

  cout<<"\n\t\t\tEnter your choice:-> ";

  cin>>w;

  switch(w)

  {

    case 1:  bus[p].install();

      break;

    case 2:  bus[p].allotment();

      break;

    case 3:  bus[0].show();

      break;

    case 4:  bus[0].avail();

      break;

    case 5:  exit(0);
    default :cout<<"enter correct choice again!...";
        break;

  }

}

return 0;

} 

