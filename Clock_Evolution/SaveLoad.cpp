#include "stdfax.h";

/*	cout << "Is this:\n (1)A new project\n (2)An existing project?\n";
	cin >> proj;
	if (proj == 2)
	{  Load();  }
	else if (proj == 1)*/
		fstream myfile;
	myfile.open("matrix test.txt", ios::out);
	if(myfile)
	{
		for(int i=1;i<3;i++)
		{
			Clock clk(0,i);
			myfile << clk.show();
		}
	}
	myfile.close();
/*	else
	{
		cout << "Input unexpected, terminating.  Oh those poor, wasted CPU cycles.\n";
		_exit(1);
	}*/