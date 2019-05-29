#include<iostream>
#include<cstdlib>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<string.h>
int rowA=0;
int colA=0;
using namespace std;
string num[20],rest[20],cui[20],addr[20],star[20],cf2[20];
string dnum[20],dname[20],dprice[20];
int iter=0;
class restaurant
{
	protected:
	string name;
	string number;
	string cuisine;
	string address;
	string rating;
	string costfr2;
	public:
		void getres();
		virtual void display();          
		void dispmenu();	
};

class bill:public restaurant
{
	protected:
	string dishnum[20],dishname[20];
	int n;                             //total number of dishes
	string price[20];
	int total,qty[20];  
	public:
		bill()
		{
		n=0;
		total=0;
		}
     	void getbill();
		void calculate();
	
		
};

class delivery:public bill
{
	char del_adr[100];
	int ph_no;
	int dist;
	int charge;
	int cost_km;
	public:
		delivery()
		{
			charge=0;
			cost_km=0;
		}
		void del();
		void display();
		void calc();
		void displaybill();
	 friend void operator +=(delivery &,delivery &);
};

void restaurant::getres()
{
	int flag=0;
	cout<<"\nEnter the restaurant number of your choice\n";
    val:cin>>number;
    
	stringstream num(number); //convert string to number
	int conv=0;
	num>>conv;
	
	for(int i=1;i<rowA;i++)
	{
		if(conv==i)		
		{
			flag++;
			name=rest[i];
			cuisine=cui[i];
			address=addr[i];
			rating=star[i];
			costfr2=cf2[i];
			break;
		}
	}
	if(flag==0)
	{
		cout<<"\nEnter a valid restaurant number\n";
		goto val;
	}
}

void restaurant::display()
{
	cout<<"\nYou Chose:\n";
	cout<<"Restaurant no. :    "<<number<<"\n"<<"Restaurant Name :   "<<name<<"\n";
	cout<<"Cuisine :           "<<cuisine<<"\n"<<"Rating :            "<<rating<<"\n"<<"\n\n\n";
}

void restaurant::dispmenu()
{
	string lineA1;
	string x1;
	 rowA=0;
	 colA=0;
	string arrayA1[20][20]={{"0"}};
	ifstream fileIN1; 
	
	stringstream num1(number);    //converts string to number
	int conv1=0;
	num1>>conv1;
   
	switch(conv1)    
	{
		case 1: fileIN1.open("TheGrillHouse_1.txt"); break;
		case 2: fileIN1.open("PunjabiDhaba_2.txt"); break;
		case 3: fileIN1.open("UpSouth_3.txt"); break;
		case 4: fileIN1.open("JuiceJunction_4.txt"); break;
		case 5: fileIN1.open("ChinaPearl_5.txt"); break;
		case 6: fileIN1.open("CornerHouse_6.txt"); break;
		case 7: fileIN1.open("Cafe_Thulp_7.txt"); break;
	} 
	if(fileIN1.fail())
	{
		cerr<<"\nFile Error Ocurred!\n";
		exit(1);
	}
	while(fileIN1.good())
	{
		while(getline(fileIN1,lineA1)) //default delimiter newline, lineA1 has rows from fileIN1 
		{
			istringstream streamA(lineA1); //streamA has address of lineA1
			colA=0;
			while(streamA>>x1) //word by word>>x
			{
				arrayA1[rowA][colA]=x1;
				colA++;
			}
			rowA++;
		}
	}
	for(int i=0;i<rowA;i++)
	{
		for(int j=0;j<colA;j++)
		{
			cout<<left<<setw(10)<<arrayA1[i][j]<<"\t\t";
		}
		cout<<"\n";
	}
	
	
	for(int j=0;j<colA;j++)
	{ 
		for(int i=0;i<rowA;i++)
		{
			if(j==0) dnum[i]=arrayA1[i][j]; 
			if(j==1) dname[i]=arrayA1[i][j];  
			if(j==2) dprice[i]=arrayA1[i][j];
	    }
    }

}



void bill::getbill()
{   int flag=0;
	int choice;

    int c=0;
    do
    { 
	     
    	cout<<"\nEnter the dish number of your choice\n";
    l2:	cin>>dishnum[c];
       
    	stringstream num(dishnum[c]); //string to int
		int conv=0;
		num>>conv;
		
		   	for(int i=1;i<rowA;i++)
		{	
			if(conv==i)			
			{	
				flag++;      
				dishname[c]=dname[i]; 
				price[c]=dprice[i];
				break;
			}
		}
		
		if(flag==0)
		{
			cout<<"\nEnter a valid dish number\n";
		goto l2;
		}
		else
		{                                              
			cout<<"\nEnter the quantity\n";
			cin>>qty[c];
			
			n++;
			c++;			
			cout<<"\nDo you want to order another dish?\n Enter 1 to continue 0 to quit\n ";
			cin>>choice;
	
	
		}
    } while(choice);
    
}

void bill::calculate()

{    cout<<"\n\n";
 
    int amt[50];
     
	     for(int i1=0;i1<n;i1++)
    {  
	    	stringstream num(price[i1]);
		int pr=0;
		num>>pr;
		
		
    	amt[i1]=pr*qty[i1];  
    	total+=amt[i1];
    	
			}
    
}

void operator += (delivery &d1,delivery &d0)
{
	int m=0;
	d1.total=d1.total+d0.total;
	int k=d1.n;
	d1.n=d1.n+d0.n;

	for(int z=k;z<d1.n;z++)
	{
		d1.dishnum[z]=d0.dishnum[m];
		d1.dishname[z]=d0.dishname[m];
		d1.price[z]=d0.price[m];
		d1.qty[z]=d0.qty[m];
		m++;
	}

}

void delivery::displaybill()
{
	int i,pay,tax=0;
	cout<<"\n______________________________________________________________________________________________________________________\n";
	cout<<"\n    Sl.No          Dish Number            Dish Name                     Price                      Qty";
	cout<<"\n_______________________________________________________________________________________________________________________\n";
	
	for(i=0;i<n;i++)
	{
	    cout<<"   "<<i+1<<"  \t\t   "<<dishnum[i]<<" \t\t    "<<dishname[i]<<"    \t\t\t"<<price[i]<<"\t\t\t     "<<qty[i]<<"\n";
	}
	cout<<"\n\n\n";
	
	cout<<"Total:                        "<<total-charge<<"\n\n";
	cout<<"Delivery charge:              "<<charge<<"\n\n";
    float gst=0.05*total;
    cout<<"GST:                          "<<gst<<"\n\n";
    float finaltotal=total+gst;
    cout<<"------------------------------------------------\n";
    cout<<"Your final bill amount is Rs. "<<finaltotal<<"\n";
    cout<<"------------------------------------------------";

	//cout<<"Total+tax"<<total<<"+"<<tax<<"="<<(total+tax)<<"\n";
}

void delivery::del()
{
	cout<<"\nEnter the delivery address\n";
	cin>>del_adr;
	cout<<"\nEnter your contact number\n";
	cin>>ph_no;
	
}

void delivery::display()
{ cout<<"\n\n";
    dist=(rand()%20)+2;
    cost_km=10;
	cout<<"Your delivery location is "<<dist<<" km away\n";
	cout<<"Delivery expected in "<<(rand()%20)+3<<" Minutes\n";
}

void delivery::calc()
{
	charge=dist*cost_km;
	total+=charge;
	//cout<<"\nTotal amount with delivery charges ="<<total;
}

int main(void)
{
	int dmode,i=0,k=1;
	delivery *d;
	d=new delivery[10];   //DMA
	

    while(k)
    { string lineA;
	string x;
	string arrayA[10][10]={{"0"}};
    ifstream fileIN;
    	rowA=0;colA=0;
	fileIN.open("RestaurantList.txt");
	
	
	if(fileIN.fail())
	{
		cerr<<"\nFile Error Ocurred!\n";
		exit(1);
	}
	
	
	
	while(fileIN.good())
	{
		while(getline(fileIN,lineA))
		{
			istringstream streamA(lineA);
			colA=0;
			while(streamA>>x)
			{
				arrayA[rowA][colA]=x;
				colA++;
			}
			rowA++;
		}
	}
	
	
	
		for(int i=0;i<rowA;i++)
		{
			for(int j=0;j<colA;j++)
			{
				cout<<left<<setw(10)<<arrayA[i][j]<<"\t";
			}
			cout<<endl<<"\n";
      	}
  	 	for(int j=0;j<colA;j++)
		{ 
			for(int i=0;i<rowA;i++)
				{   
        			if(j==0) num[i]=arrayA[i][j];
	     			if(j==1) rest[i]=arrayA[i][j];
	     			if(j==2) cui[i]=arrayA[i][j];
	    			if(j==3) star[i]=arrayA[i][j];
	    			if(j==4) cf2[i]=arrayA[i][j];
	     			if(j==5) addr[i]=arrayA[i][j];
	        	}
    	}
      
	    d[iter].getres();
	    d[iter].restaurant::display();
	    fileIN.close();
	    d[iter].dispmenu();
	    d[iter].getbill();
	    d[iter].calculate();
	    if(iter!=0)
	    {
	    	d[iter]+=d[iter-1];
		}
	    cout<<"\nDo you want to choose from another restaurant?\nEnter 1 for yes 0 for no\n";
	    cin>>k;
	    if(k==1) iter++;
    }
    
      //cout<<"iter"<<iter;
    
	cout<<"\nChoose mode of delivery\n1-Home Delivery\n2-Take away\n";
	cin>>dmode;

	if(dmode==1)
	{
	   d[iter].del();
       d[iter].display();
       d[iter].calc();
    }
     
	d[iter].displaybill();
	cout<<"\n\n\n\n\n\n\t\t\t----------Thank You!!-----------\n\n";
	return 0;
 } 
