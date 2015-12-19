#include<bits/stdc++.h>
using namespace std;

string remove_extra_spaces(string line) {
	int i,f=0;
	for(i=0;i<line.size();i++) {
		if(line[i]!=' ') {
			f = 1;
			break;
		}
	}
	if(f == 0)
	i++;
	string st="";
	for(;i<line.size()-1;i++) {
		if(line[i] ==' ' && line[i+1] ==' ')
		continue;
		st += line[i];
	}
	if(line[i]!=' ')
	st += line[i];
	return st;
}


pair<int,float>  find_rating(string line) {
//	cout << line <<"\n";
	int i,c=0;
	int j,k;
	for(j=1;j<line.size();j++) {
//		printf("line[%d]=%c\n",j,line[j]);
		if(line[j]=='[') {
			i = j;
		} else if(line[j]==']') {
			k = j;
			break;
		}
	}
//	printf("%d %d\n",i,k);
	i++;

	float rating = 0;	
	for(;i<k;i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(isdigit(line[i])) {
			rating = line[i] - 48;
			if(line[i+1] == '.') {
				float p = (line[i+2]-48);
				rating =rating + p/10;
			}
			break;
		}
	}
//	printf("dfd %f\n",rating);
	if(rating == 0)
	rating = -1;
	return make_pair(k+1,rating);
}

pair<int,int> find_price(string line,int start) {
	int i,j,k;
	for(i=start;i<line.size();i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(line[i]=='[')
		j = i;
		else if(line[i] == ']') {
			k = i;
			break;
		}
	}
//	printf("%d %d\n",j,k);
	j++;
	int flag;
	int price = 0;
	for(i=j;i<k;i++) {
		if(isdigit(line[i]) == 1) {
			price = price *10 + (line[i]-48);
		}
	}
	if(price == 0)
	price = -1;
	return make_pair(k+1,price);
}


pair<int,string> find_link(string line) {
//	cout << line <<"\n";
	int i,c=0,c1=0,j,k;
	for(i=1;i<line.size();i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(line[i] =='[')
		c++;
		if(line[i]==']')
		c1++;
		if(c == 3) {
			j = i;
			c = 0;
		}
		if(c1 == 3) {
			k = i;
			break;
		}
	}
//	printf("%d %d\n",j,k);
	i = j;
	string st ="http://www.flipkart.com";
	for(;i<line.size();i++) {
		if(line[i]=='"')
		break;
	}
	i++;
	for(;i<k-1;i++) {
//		printf("line[%d]=%c\n",i,line[i]);
//		cout << st <<"\n";
		st += line[i];
	}
	return make_pair(k+1,st);
}

pair<int,string> find_image_link(string line,int start) {
	int i,j,k;
//	printf("yes\n");
	for(i=start;i<line.size();i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(line[i] =='[')
		j = i;
		else if(line[i]==']') {
			k = i;
			break;
		}
	}
//	printf("j=%d k = %d\n",j,k);
	i = j;
	i++;
	for(;i<line.size();i++) {
		if(line[i]=='"')
		break;
	}
	i++;
	string st ="";
	for(;i<line.size();i++) {
		if(line[i]=='"' && line[i+1]==']')
		break;
		st += line[i];
	}
	return make_pair(k+1,st);
}

pair<int,string> find_company_name(string line, int start) {
	int i,j,k;	
	int c =0,c1=0;
	//printf("line[%d]=%c\n",i,line[i]);
	for(i=start;i<line.size();i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(line[i]=='[')
		c++;
		if(line[i]==']') 
		c1++;
		if(c == 3) {
			j = i;
			c = 0;
		} 
		if(c1 == 3) {
			k = i;
			break;
		}
	}
//	printf("%d %d\n",j,k);
	i = j+1;
	for(;i<line.size();i++) {
		if(line[i]=='"')
		break;
	}
	i++;
	string st="";
	i = i+3;
	for(;i<k;i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(line[i]==' ')
		break;
		st += line[i];
	//	cout << st;
	}
	return make_pair(i+1,st);
}

pair<int,string> remove_extra(string line,int start) {
	int i,j,k;
	for(i=start;i<line.size();i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(line[i] == ']')
		break;
	}
	k = i+1;
	string st = "";
	char remove[] ={',','-','"','(',')','{','}','[',']','+','|','/','\n','\t','\\'};
	int size = sizeof(remove) / sizeof(char); 

	for(i=start;i<line.size();i++) {
		for(j=0;j<size;j++)  {
			if(remove[j]==line[i])
			break;
		}
		if(j!=size) {
			st += (char)32;
		}
		else {
			if(i>0 && line[i]=='.' && isalnum(line[i-1])==false)
			continue;
			st += line[i];
		}
	}
//	cout <<"st " <<st<<"\n";
	
	string s2="";
	for(i=0;i<st.size()-1;i++) {
		if(st[i]==st[i+1] && st[i]==' ')
		continue;
		s2 += st[i];
	}
	if(s2[s2.size()-1]==' ')
	s2.erase(s2.begin()+s2.size()-1);
	return make_pair(k,s2);
}


pair<int,string> remove_extra_without_braces(string line,int start) {
	int i,j,k;
	for(i=start;i<line.size();i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(line[i] == ']')
		break;
	}
	k = i+1;
	string st = "";
	char remove[] ={',','-','"','{','}','[',']','+','|','/','\\','"'};
	int size = sizeof(remove) / sizeof(char); 

	for(i=start;i<line.size();i++) {
		for(j=0;j<size;j++)  {
			if(remove[j]==line[i])
			break;
		}
		if(j!=size) {
			st += (char)32;
		}
		else {
			if(i>0 && line[i]=='.' && isalnum(line[i-1])==false)
			continue;
			st += line[i];
		}
	}
//	cout <<"st " <<st<<"\n";
	
	string s2="";
	for(i=0;i<st.size()-1;i++) {
		if(st[i]==st[i+1] && st[i]==' ')
		continue;
		s2 += st[i];
	}
	if(s2[s2.size()-1]==' ')
	s2.erase(s2.begin()+s2.size()-1);
	return make_pair(k,s2);
	
}
string lower_case(string line) {
	int i;
	string ss = line,ss1="";
	for(i=0;i<ss.size();i++)
	ss1 += tolower(ss[i]);
	return ss1;
}

string remove_color_name (string line,string color) {
	if(color.compare("NULL")==0) {
		string line1 ="";
		for(int i=0;i<line.size()-3;i++)
		line1 += line[i];
		return line1;
	}
//	cout << line <<" " << color <<"\n";
	int i;
	vector<string> check;
	string st ="";
	for(i=0;i<color.size();i++) {
		if(color[i] == ' ') {
			check.push_back(st);
			st = "";
		} else
			st += color[i];
	}
	if(color[i-1]!=' ')
	check.push_back(st);

//	for(i=0;i<check.size();i++)
//	cout << check[i] <<"\n";

	int j,k,count1 = 0;
	int q =1;
	while(q--) {
		st = check[count1];
		for(i=0;i<line.size()-st.size();i++) {
			for(j=0;j<st.size();j++) {
//				printf("st[%d]=%c line[%d]=%c\n",j,st[j],i,line[i]);
				if(st[j] != line[i+j]) {
					break;
				}
			}
			if(j == st.size()) {
				count1++;
				string line1 ="";
				for(k=0;k<i;k++)
				line1 += line[k];
//				printf("%d %d\n",(i+st.size()),line.size()-3);
				for(k=i+st.size();k<line.size();k++) {
					line1 += line[k];
//					cout << "line " << line1 <<"\n";	
				}

				line = line1;
//				cout << "line " << line <<"\n";
				break;
			}
		}
//		printf("\n\n");
		if(count1 == check.size())
		break;
	}
//	cout <<line<<"\n";
	string line1 ="";
	for(i=0;i<line.size()-7;i++)
	line1 += line[i];
	return line1;

}

string remove(string line) {
	string st ="";
	for(int i=0;i<line.size();i++) {
		if(line[i]==',')
		continue;
		st += line[i];
	}
	return st;
}

string remove_braces(string line) {
	int i,flag = 0;
	string line1 ="";
	for(i=0;i<line.size();i++) {
		if(flag == 1)
		continue;
		if(line[i] == '(') {
			flag = 1;
		}else if(line[i] == ')')
			flag = 0;
		else
			line1 += line[i];
	}
	return line1;	
}

string remove_reserved_keyword(string line) {
	ifstream inp2("reserve_keyword.txt");
	vector<string>check;
	string line1;
	while(getline(inp2,line1)) {
		check.push_back(line1);
	}
	vector<string> s;
	int i,j,k;
	string st ="";
	for(i=0;i<line.size();i++) {
		if(line[i]==' ') {
			s.push_back(st);
			st = "";
		} else 
			st += line[i];
	}
	if(st.compare(" ")!=0)
	s.push_back(st);
	line ="";
	for(i=0;i<s.size();i++)	 {
		for(j=0;j<check.size();j++) {
			if(check[j].compare(s[i])==0)
			break;
		} 
		if(j == check.size()) 
		line += s[i];
		if(i != s.size())
		line += ' ';
	}
	inp2.close();
	return line;
}


pair<string,string> find_color(string line,int start1) {
	string copy = line;
//	cout << line <<"\n";
	ifstream inp3("color.txt");
	string line1;
	vector<string> color;
	while(getline(inp3,line1)) 
	color.push_back(line1);
//	string color[]={"blue","grey","silver","orange","red","yellow","green","brown","gold","black","white","deep blue","pristine white","pure white","titanium","magnetic black","milkyway grey","black blue","grey silver","milkyway grey","sandstone black","midnight blue","cloud white","royal blue","black leather","black & blue","white & turquiose","bamboo white","glossy black","santroni white","Miky way grey","Glacier blue","saffron grey","dark grey","pearl white","arctic white","matte blue","gunmetal grey","fabulous white","sliver white","metalic black","stealth black","passion red","polar white","amber gold","black stone","stealth black","brown gray","prussian blue","hot blue","god black","black gold","pebble blue","marble white","charcoal grey","ceramic white","midnight black","deep black","shimmery white","indigo blue","white frost","jet black","copper gold","champagne gold","noble black","white frost","black mist","classic white","electric blue","frosted gold","chic white","black gold","blush pink","dazzling white","bronze gold","metalic blue","wine red","titanium grey","splash blue","iris charcoal","copper gold","shimmery white"};
	int size = color.size();	
	vector<string> s;
	int i,j,k;
	string st ="";
	for(i=0;i<line.size();i++) {
		if(line[i]==' ') {
			s.push_back(st);
			st = "";
		} else 
			st += line[i];
	}
	if(st.compare(" ")!=0)\
	s.push_back(st);
	int start,end;
	string col ="";
	for(i=0;i<size;i++) {
//		cout <<"color["<<i <<"]=" << color[i] <<"\n";
		vector<string> temp;
		string cc = color[i];
//		cout << cc <<"\n";
		st = "";
		for(j=0;j<cc.size();j++) {
			if(color[i][j]==' ') {
				temp.push_back(st);
				st = "";
			} else 
				st += cc[j];
//			cout <<"st " <<st <<"\n";
		}
		if(cc[j]!= ' ' )
		temp.push_back(st);

		for(j=0;j<s.size();j++) {
			if(s[j].compare(temp[0]) == 0)
			break;
		}
		if(j == s.size()) 
		continue;
		int t = j;
//		cout <<"t " << t <<"\n";
		if(temp.size()==1) {
			start = j;
			end = j+1;
			col = color[i];
//			cout <<i <<" " << col <<"\n";
			continue;
		}

		j++;
		for(k=1;k<temp.size() && j < s.size();k++) {
			if(temp[k].compare(s[j])!=0)
			break;
		}
		if(k == temp.size()) {
			start = t;
			end  = j+1;
			col = color[i];
//			cout << col <<"\n";
		}
//		cout << start <<" "<< end <<"\n";
	}
	if(col.size()==0)
	return make_pair(line,"NULL");
//	cout <<line <<" " ;
//	printf("%d %d\n",start,end);
	line = "";
	for(i=0;i<s.size();i++) {
		if(i>=start && i<end)
		continue;
		line  += s[i];
		if(i!=s.size()-1)
		line += ' ';
	}	
	return make_pair(line,col);
}

pair<int,string> find_rom(string line) {
//	cout << "line " << line <<"\n";
	int i,j,q;
	for(i=0;i<line.size()-1;i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(line[i]=='g' && line[i+1]=='b' && i+2 == line.size())
		break;
		else if(line[i]=='g' && line[i+1]=='b' && i+2 < line.size() && (line[i+2]==' ' || line[i+2]==')' || line[i+2]==','))
		break;
	}
	if(i == line.size()-1) {
//		printf("dfsef\n");
		return make_pair(-10,line);
	}
//	printf("yes\n");
	int x = 0;
	q = i;
	for(i=i-2;i>=0;i--) {
		if(line[i]==' ')
		break;
		x = x*10 + (line[i]-48);
	}
//	printf("x =%d\n",x);
	int x1=0;
	while(x!=0) {
		x1 = x1*10 + (x%10);
		x = x/10;
	}
	string st="";
	for(j=0;j<=i;j++) {
		st += line[j];
//		cout <<"st "<< st <<"\n";
	}
	for(i=q+3;i<line.size();i++) {
		if(line[i]=='r') {
			i = i+2;
		} else
			st += line[i];
//		cout <<"st "<< st <<"\n";
	}
	return make_pair(x1,st);
}


string rm(string line) {
	string line1="";
	for(int i=0;i<line.size();i++) {
		if(line[i]==92)
		continue;
		if(line[i]==34) {
			i++;
			continue;
		}
		line1 += line[i];
	}
	return line1;
}
int main(int argc,char *argv[]) {
	//cout<<argv[1]<<" "<<argv[2];
//	string x(argv[3]);
	int i,p;
//	ifstream inp(argv[1]);
	ifstream inp("shank2.json");
	ofstream input,output;
	string line1,line2,line3,line4;
	input.open("p.txt");
	output.open("2nd.txt");
//	input.open(argv[2]);
//	output.open(argv[4]);
//	getline(inp,line1);
	input <<"use mobile_store;\n";
	while(getline(inp,line1)) {	
		input << "insert into mobile values(";		
		getline(inp,line2);	
		line3 = remove_extra_spaces(line1);		
		line4 = remove_extra_spaces(line2);
		
		pair<int,string> pp = find_link(line3);
		string  product_link = pp.second;

		pair<int,string> pp1 = find_image_link(line3,pp.first);
		string  image_link = pp1.second;
		
		pair<int,float> pp2 = find_rating(line4);
		float rating = pp2.second;
		
		pair<int,int> pp3 = find_price(line4,pp2.first);
		int price = pp3.second;
		

		pair<int,string> pp4 = find_company_name(line4,pp3.first);
		string company = lower_case(pp4.second);
		
		pair<int,string> pp5 = remove_extra(line4,pp4.first);			

		pair<string,string> pp6 = find_color(lower_case(pp5.second),pp4.first);
		string color = pp6.second;


		pair<int,string> pp7 = remove_extra_without_braces(line4,pp4.first);					
		string line5="";
		for(i=pp4.first;i<line4.size();i++)
		line5 += tolower(line4[i]);
		line5 = remove_color_name(line5,color);
		line5 = remove(line5);

		pair<int,string> pp8 = find_rom(line5);	
		int rom = pp8.first;

//		input <<pp8.second <<",\n";

		line5 = remove_braces(pp8.second);
//		input <<line5 <<"\n";

		string line6 = remove(line5);
//		input <<line6 <<"\n";
//		cout << line6<<"\n";
		string product_description=remove_reserved_keyword(line6);		
		product_description=remove_extra_spaces(product_description);
		product_description = rm(product_description);


		input <<"\""<<company<<"\",";			

		input <<"\""<<product_description<<"\",";

		if(price == -1.0)
		input <<"NULL,";
		else
		input << price <<",";

		if(rating == -1.0)
		input <<"NULL,";
		else
		input <<rating<<",";

		input <<"\""<<color<<"\",";				

		if(rom == -10)
		input <<"NULL,";
		else
		input <<rom <<",";

		input <<"\""<<product_link<<"\",";

		input <<"\""<<image_link<<"\",";
		input <<"\"flipkart\",\n";
//		input <<"\""<<x<<"\");\n";
		
		output <<company<<"\n";
		output <<product_description<<"\n";
		output <<product_link<<"\n";
	}
	input.close();
	return 0;
}
