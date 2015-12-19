#include<bits/stdc++.h>
using namespace std;

string remove_extra_spaces(string line) {
	int i,f = 0;
//	cout <<"string "<<line<<"\n";
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
//		cout <<st<<"\n";
	}
	if(line[i]!=' ')
	st += line[i];
	return st;
}


pair<int,float>  find_rating(string line) {
	int i,c=0;
	int j,k;
	for(j=1;j<line.size();j++) {
		if(line[j]=='[') {
			i = j;
		} else if(line[j]==']') {
			k = j;
			break;
		}
	}
	i++;
	if(i == k)
	return make_pair(k+1,-1.0);
	
	for(;i<k;i++) {
		if(line[i]=='"')
		break;
	}
	i++;
	string st="";
	float rating;
	for(;i<line.size();i++) {
		if(isdigit(line[i])) {
			rating = line[i] - 48;
			if(line[i+1] == '.') {
				float p = (line[i+2]-48);
				rating =rating + p/10;
			}
			return make_pair(k+1,rating);
		}
	}
}

pair<int,int> find_price(string line,int start) {
	int i,j,k;
	for(i=start;i<line.size();i++) {
		if(line[i]=='[')
		j = i;
		else if(line[i] == ']') {
			k = i;
			break;
		}
	}
	j++;
	int flag;
	for(i=j;i<k;i++) {
		if(line[i]=='"') {
			if(isalpha(line[i+1])==1) {
				flag = 1; 
				break;
			}
			else {
				flag = 0;
				break;
			}
		}  
	}
	int price = 0;
	if(flag == 1) {
		i++;
		for(;i<k;i++) {
			if(line[i]=='"')
			break;
		}
		i++;
		for(;i<k;i++) {
			if(line[i]=='"')
			break;
		}
		i++;

		for(;i<k-1;i++) {
			if(isdigit(line[i])==1) {
				price = price *10 + (line[i]-48);
			} else if(line[i] =='.')
				break;
		}
	} else {
		i++;
		for(;i<k-1;i++) {
			if(isdigit(line[i])==1) {
				price = price *10 + (line[i]-48);
			} else if(line[i] =='.')
				break;			
		}
	}
	return make_pair(k+1,price);
}


pair<int,string> find_link(string line,int start) {
	int i;
	for(i=start;i<line.size();i++) {
		if(line[i] =='[')
		break;
	}
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
	return make_pair(i+2,st);
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
	//printf("line[%d]=%c\n",i,line[i]);
	for(i=start;i<line.size();i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(line[i]=='[')
		j = i;
		else if(line[i]==']') {
			k = i;
			break;
		}
	}
	i = j+1;
	for(;i<line.size();i++) {
		if(line[i]=='"')
		break;
	}
	i++;
	string st="";
	for(;i<line.size();i++) {
		if(line[i]==' ')
		break;
		st += line[i];
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
	char remove[] ={',','-','"','(',')','{','}','[',']','+','|','/'};
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

pair<string,string> find_color(string line) {
//	cout << line <<"\n";
	string color[]={"blue","grey","silver","orange","red","yellow","green","brown","gold","black","white","deep blue","pristine white","pure white","titanium","magnetic black","milkyway grey","black blue","grey silver","milkyway grey","sandstone black","midnight blue","cloud white","royal blue","black leather","black & blue","white & turquiose","bamboo white","glossy black","santroni white","Miky way grey","Glacier blue","saffron grey","dark grey","pearl white","arctic white","matte blue","gunmetal grey","fabulous white","sliver white","metalic black","stealth black","passion red","polar white","amber gold","black stone","stealth black","brown gray","prussian blue","hot blue","god black","black gold","pebble blue","marble white","charcoal grey","ceramic white","midnight black","deep black","shimmery white","indigo blue","white frost","jet black","copper gold","champagne gold","noble black","white frost","black mist","classic white","electric blue","frosted gold","chic white","black gold","blush pink","dazzling white","bronze gold","metalic blue","wine red","titanium grey","splash blue","iris charcoal","copper gold","shimmery white"};
	int size = sizeof(color)/sizeof(string);	
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
//	cout << line <<" " << col <<"\n";
	return make_pair(line,col);
}

pair<int,string> find_rom(string line) {
	int i,j,q;
	for(i=0;i<line.size()-1;i++) {
//		printf("line[%d]=%c\n",i,line[i]);
		if(line[i]=='g' && line[i+1]=='b' && i+2 == line.size())
		break;
		else if(line[i]=='g' && line[i+1]=='b' && i+2 < line.size() && line[i+2]==' ')
		break;
	}
	if(i == line.size()-1) {
		return make_pair(-10,line);
	}
	int x = 0;
	q = i;
	for(i=i-1;i>=0;i--) {
		if(line[i]==' ')
		break;
		x = x*10 + (line[i]-48);
	}
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

string lower_case(string line) {
	int i;
	string ss = line,ss1="";
	for(i=0;i<ss.size();i++)
	ss1 += tolower(ss[i]);
	return ss1;
}
int main(int argc,char *argv[]) {
	string x="212";
	int i,p;
	ifstream inp("1.json");
	ofstream input,output;
	string line,line1;
	input.open("amazon_output.txt");
	output.open("2.txt");
//	getline(inp,line1);
//	cout << line1 <<"\n";	
//	input <<"use mobile_store;\n";
	
	while(getline(inp,line1)) {	
		input << line1<<"\n";
		line = remove_extra_spaces(line1);	
		
			
		pair<int,float > pp = find_rating(line);
		float rating = pp.second;
		input << rating << "\n";		
	
/*		pair<int,int> pp1 = find_price(line,pp.first);
		int price = pp1.second;
		input << price<<"\n";
		
		pair<int,string> pp2 = find_link(line,pp1.first);
		string product_link = pp2.second;

		pair<int,string> pp3 = find_image_link(line,pp2.first);
		string image_link = pp3.second;

		pair<int,string> pp4 = find_company_name(line,pp3.first);
		string company = lower_case(pp4.second);
		
		pair<int,string> pp5 = remove_extra(line,pp4.first);			
		pair<string,string> pp6 = find_color(lower_case(pp5.second));
		string color = pp6.second;

		pair<int,string> pp7 = find_rom(pp6.first);	
		int rom = pp7.first;
		
		string product_description = pp7.second;
		product_description=remove_reserved_keyword(product_description);		
		product_description=remove_extra_spaces(product_description);
//		cout << product_description<<"\n";		

		input <<"insert into mobile values(";
		input <<"\""<<company <<"\",";		
		input <<"\""<<product_description <<"\",";		
		input <<price <<",";		

		if(rating == -1.0)
		input <<"NULL,";
		else		
		input <<rating <<",";		

		if(color =="NULL")
		input <<"NULL,";		
		else
		input <<"\""<<color <<"\",";

		if(rom == -10)		
		input <<"NULL,";
		else
		input <<rom <<",";		

		input <<"\""<<product_link <<"\",";		
		input <<"\"amazon\",";
		input <<"\""<<x<<"\",";
		input <<"\""<<image_link <<"\");\n";		

		output<<company<<"\n";
		output<<product_description<<"\n";
		output<<product_link<<"\n";

*/	}
	input.close();
	output.close();
	return 0;
}
