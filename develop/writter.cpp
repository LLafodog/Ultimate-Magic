#include<iostream>
#include<fstream>
#include<string> 

using namespace std;

bool askYesNo(string question="Are you sure ?")
// Yes No Question
{
  cout << question << " (y/n)" << endl;
  char ans; cin >> ans;
  return (ans=='o' || ans=='O' || ans=='y' || ans=='Y');
}

string writeTextureLine()
// return a line to write in the all_texture.txt file
{
      // TYPE
      char indicator='X';
      cout << " Has the texture you wanna add a particle that corresponds ? ";
      if(askYesNo("")){indicator='P';}else{indicator='S';}

      // NAME
      string name="";
	  cout << " What is the texture name ? (WARNING: .PNG ONLY) \n";
	  cin >> name;

      // NB FRAMES X
      string nb_x="";
	  cout << " How many frames (horizontally) has the texture file ? \n";
	  cin >> nb_x;

      // NB TEXTURES Y
      string nb_y="";
	  cout << " How many animations (vertically) has the texture file ? \n";
	  cin >> nb_y;

      // WIDTH
      string width="";
	  cout << " What is the basic width in the texture file ? \n";
	  cin >> width;

      // HEIGHT
      string height="";
	  cout << " What is the basic height in the texture file ? \n";
	  cin >> height;
	  cout << " You input the number : \n" << height;

      // frameD, animD, random
      string frameD="100", animD="1000";
      bool random=false;
      cout << " Would you like to define the animation ? \n";
      if(askYesNo(""))
	{
	  // frameD
	      cout << " What is the basic delay (between frames) you want for the animation ? \n";
	      cin >> frameD;

	  // animD
	      cout << " What is the basic delay (between Animation) you want for the animation ? \n";
	      cin >> animD;

	  // random
	      cout << " Shall the animation be randomly reset ? \n";
	      random=askYesNo("");
	}

      // RESULT
      string space=" ";
      string booltostr; if(random){booltostr="true";}else{booltostr="false";}
      string res=indicator+space+name+space+nb_x+space+nb_y+space+width+space+height+space+frameD+space+animD+space+booltostr;
      return res;
}

int main()
{
  // menu ?
  string answer="";
  string result="";
  ofstream writter("test.txt",ofstream::app);
  if(writter)
    {
      cout << " === ADD A TEXTURE === " << endl;
      while (answer!="end")
	{
	  if(answer!="end")
	    {
	      result="lol haha bim";//writeTextureLine();
	      cout << " You get the line : " << result << endl;
	      if(askYesNo("Shall I write it in the file ? ")){writter << result;}
	      else{ cout << " Thanks for the waste :'( " << endl;}
	    }
	  cout << " If you wanna end it, enter ""end"" know, else type anything. " << endl;
	  cin >> answer;
	}

    }
  writter.close();
  cout << " ===== END ======== " << endl;

  return 0;
}
