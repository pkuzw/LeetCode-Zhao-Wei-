///@file	Group Shifted Strings
///@author	zhaowei
///@date	2016.01.14
///@versin	1.0

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
	///@brief	包含有原来字符串和字符串字符之间偏移量的类
	class shiftString {
	public:
		shiftString() {
			str = "";
		}
		shiftString(string a) {
			str = a;
			if (str.size() == 1)	offset.push_back(0);
			else
				for (int i = 1; i != str.size(); i++)
					offset.push_back(str[i] - str[i-1] < 0 ? str[i] - str[i-1] + 26 : str[i] - str[i-1]);
		}

		string str;			//	原字符串
		vector<int>	offset;	//	偏移量数组：s[i] - s[i-1]的值，当其小于0时，加上26
	};

public:
	///@brief	给能够通过平移转换的字符串划分成组
	///@param	strings	散乱的字符串数组
	///@return	划分成组的字符串组
	///@note	1. 同一组的字符串的长度一定相同，且各个相邻字符之间的差值（后者减去前者的的值相同，如果为负，则加上26）相同；
	//			2. 新建一个类，能够保存字符串和字符串字符之间的偏移量；
	//			3. 然后根据字符串的长度以及它内部字符之间的偏移量来进行归类；
	//			4. 然后对二维字符串数组进行排序即可。这一步可以进行优化，在上面的归类时进行插入排序就行。
	//			5. 时间复杂度为O(n^2k)，空间复杂度为O(nk)，n为字符串数目，k为字符串长度。
	vector<vector<string>> groupStrings(vector<string>& strings) {
		vector<vector<string>> empty_rslt;
		if (strings.empty())	return empty_rslt;
		vector<shiftString> sstrs;		
		for (int i = 0; i != strings.size(); i++) {
			shiftString sstr(strings[i]);				
			sstrs.push_back(sstr);
		}
		vector<vector<string>> rslt;
		for (int i = 0; i != sstrs.size(); i++) {
			if (rslt.empty()) {
				vector<string> tmp;
				tmp.push_back(sstrs[i].str);
				rslt.push_back(tmp);				
			}
			else {
				bool flg_found = false;	// 标记是否能够插入已经存在的字符串数组
				for (int j = 0; j != rslt.size(); j++) {
					if (sstrs[i].str.size() == rslt[j][0].size()) {
						int k = 0;
						bool flg_single = false;
						for (k = 0; k != sstrs[i].offset.size(); k++) {
							if (sstrs[i].str.size() == 1) {
								rslt[j].push_back(sstrs[i].str);
								flg_single = true;
								flg_found = true;
							}
							else {
								int offset_rslt = rslt[j][0][k+1] - rslt[j][0][k] < 0 ? rslt[j][0][k+1] - rslt[j][0][k] + 26 : rslt[j][0][k+1] - rslt[j][0][k];
								if (sstrs[i].offset[k] != offset_rslt)	break;
							}
						}
						if (k == sstrs[i].offset.size() && !flg_single) {
							rslt[j].push_back(sstrs[i].str);
							flg_found = true;
						}
					}					
				}
				if (!flg_found) {
					vector<string> tmp;
					tmp.push_back(sstrs[i].str);
					rslt.push_back(tmp);
				}
			}
		}
		for (int i = 0; i != rslt.size(); i++)	sort(rslt[i].begin(), rslt[i].end());
		return rslt;
	}
};


int main() {
	string s[8] = {"abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"};
	vector<string> strings;
	for (int i = 0; i != 8; i++)
		strings.push_back(s[i]);
	Solution slt;
	vector<vector<string>> rslt = slt.groupStrings(strings);
	return 0;
}

/*
input: ["xzv"
"tvhmtraayghfabutim"
"scruzaydxrapcuv"
"xiznzqqjbetchvhndzz"
"qmbkbjpkxzmnwvo"
"tttwsszaetyzgsaprv"
"xdhbxxxomhagohdvdyv"
"khugdmdbbqjbeuxq"
"xzzqnowcyplkdxgkbbb"
"daxzqsdcfuymlyevyfnayb"
"nrlalrdjqqckogfqlhfhg"
"akpellndulbbbipbvatbu"
"pfqeu"
"dneng"
"rjnvgxk"
"eujibxcxetdjztn"
"aufkyfjuruaq"
"izeqjoftsfzjkujiubkrb"
"dwzuyrospzjzuckk"
"kcuxsetkmzkq"
"lvej"
"lzefktml"
"varaxwjxf"
"cwdqxivcxeyzhsvqccy"
"kzxlrqbabvtvkfajbjatzyix"
"husuheaiirzowtiadgtxwf"
"swtja"
"ddvxhgesuenqdgutm"
"uaduv"
"t"
"yvwfcproumulvnbva"
"ddjikfsnasyj"
"tqxiqlqkxbmwuytempvg"
"yihridsxajkiyehmdbru"
"pbxvdoleubrdd"
"smavxt"
"azlrmjwmlsglgwrdakgn"
"cf"
"ohkaajphvrorgyx"
"nll"
"jlnlqzviffdmegnxig"
"pqgkqrancnwaqrjovjlgqsfx"
"azwaipyqlmgoeslujdkwuh"
"jubooimlfis"
"sosnjvqikiivlighyktd"
"jhujjiiovhw"
"jgbj"
"qtrbilvqvy"
"vlmkkilhsqlknvqpus"
"omuucd"
"ligpithabxjqtuaf"
"mz"
"ognmihotoqgprvbt"
"nmgwkocmeezb"
"qmiajlowymr"
"xmlmolj"
"cwciqqpbmzzcgmnrvgucezor"
"ng"
"lqglykvsxhobqrppeqrlp"
"ywuytvrproahtgro"
"etcnjqg"
"bogjahrw"
"rrrkddajfq"
"nwcraujocpk"
"yo"
"nhasjwodqyququhhfkyv"
"tpalgbgirzrl"
"jjgcsekxxi"
"r"
"jgxxttnlhez"
"ha"
"jxklqfdizkgzusrzs"
"hnjctughrsdiyezcqsmij"
"tvpawacxepvq"
"lwv"
"rspgmumnbrzk"
"gqkdxbkylirxxqrhh"
"wsbvir"
"fjktj"
"rulvjpezzonnbr"
"kxntnopkkjgliltrlklfgc"
"h"
"uplapswlksu"
"cevzkpfcbviliulexyx"
"mvbwfqqbeisdsjdnn"
"giavjwaftarskv"
"trlhxmqayeiero"
"yfazdiayalzrnf"
"qmolgaezbwuodbdhsxclhzi"
"nskgjmut"
"gccpj"
"psmqmdceprjoiw"
"dhvqyqvnh"
"jcxq"
"quvi"
"pvqdzzwv"
"yzksz"
"vnicvmnfwwwmzhsdsm"
"gn"
"jcyfpawtcnuikudwuijpd"
"mmncorzbnoawyo"
"cwygpjjmrmslabafcmwdhpdo"
"nikwaflxpepnkz"
"qmylnzkhz"
"oc"
"jnyibizgmwjqjvhbg"
"ajhaejn"
"eulboowdyd"
"vyjfniqjoepdbzulvpgjic"
"oauvt"
"vpnmjbnkf"
"izk"
"sanouetznnk"
"truufmplrmsxgvrtl"
"yuabbnxybbpfgblou"
"yjyawflsvetbdpcgbjta"
"cmozvlftrhtxmjqkorxfrql"
"nbyvnbhjlofqdtilvplcdks"
"nxmyafxvrfhbuzpzixt"
"lxtoignhwtcbsi"
"cycu"
"rlzjrirwfhwdvolixa"
"itle"
"nmitv"
"cno"
"mnwjytgktowostuzvrcjxr"
"etus"
"othjqfpysicbdhfezxpvhjd"
"nzypfebzbsaakoky"
"uimwaktcywogwptihvrrh"
"pgc"
"njwftpurketzvjbzivanz"
"olnrizftjnjixeysi"
"k"
"fbwkolpka"
"vqcxxbcumypdbetrknavgm"
"ivfnyhqqnjdmdwqslhk"
"fusfadhqfruriiglvqzuns"
"r"
"sghqrdaelollqmczagojceys"]

my output: [["h","k","r","r","t"],["cf"],["gn"],["mz"],["oc"],["yo"],["ha","ng"],["xzv"],["cno","lwv"],["izk","pgc"],["nll"],["quvi"],["lvej"],["itle"],["etus"],["jcxq"],["cycu"],["jgbj"],["yzksz"],["fjktj","swtja"],["uaduv"],["dneng"],["oauvt"],["pfqeu"],["gccpj"],["nmitv"],["smavxt"],["wsbvir"],["omuucd"],["ajhaejn"],["etcnjqg","xmlmolj"],["rjnvgxk"],["nskgjmut"],["pvqdzzwv"],["bogjahrw"],["lzefktml"],["dhvqyqvnh"],["varaxwjxf"],["vpnmjbnkf"],["fbwkolpka","qmylnzkhz"],["jjgcsekxxi","rrrkddajfq"],["qtrbilvqvy"],["eulboowdyd"],["sanouetznnk"],["nwcraujocpk"],["jubooimlfis"],["uplapswlksu"],["qmiajlowymr"],["jgxxttnlhez"],["jhujjiiovhw"],["ddjikfsnasyj"],["rspgmumnbrzk"],["tvpawacxepvq"],["kcuxsetkmzkq"],["aufkyfjuruaq"],["tpalgbgirzrl"],["nmgwkocmeezb"],["pbxvdoleubrdd"],["mmncorzbnoawyo"],["giavjwaftarskv"],["psmqmdceprjoiw","rulvjpezzonnbr"],["yfazdiayalzrnf"],["lxtoignhwtcbsi"],["nikwaflxpepnkz"],["trlhxmqayeiero"],["scruzaydxrapcuv"],["eujibxcxetdjztn"],["ohkaajphvrorgyx"],["qmbkbjpkxzmnwvo"],["nzypfebzbsaakoky"],["ognmihotoqgprvbt"],["dwzuyrospzjzuckk"],["khugdmdbbqjbeuxq","ligpithabxjqtuaf"],["ywuytvrproahtgro"],["ddvxhgesuenqdgutm"],["jnyibizgmwjqjvhbg"],["mvbwfqqbeisdsjdnn"],["gqkdxbkylirxxqrhh"],["jxklqfdizkgzusrzs"],["yuabbnxybbpfgblou"],["olnrizftjnjixeysi","yvwfcproumulvnbva"],["truufmplrmsxgvrtl"],["tttwsszaetyzgsaprv"],["jlnlqzviffdmegnxig","tvhmtraayghfabutim"],["vlmkkilhsqlknvqpus"],["vnicvmnfwwwmzhsdsm"],["rlzjrirwfhwdvolixa"],["cevzkpfcbviliulexyx","xzzqnowcyplkdxgkbbb"],["xdhbxxxomhagohdvdyv"],["nxmyafxvrfhbuzpzixt"],["xiznzqqjbetchvhndzz"],["ivfnyhqqnjdmdwqslhk"],["cwdqxivcxeyzhsvqccy"],["yihridsxajkiyehmdbru"],["yjyawflsvetbdpcgbjta"],["nhasjwodqyququhhfkyv"],["sosnjvqikiivlighyktd"],["tqxiqlqkxbmwuytempvg"],["azlrmjwmlsglgwrdakgn"],["nrlalrdjqqckogfqlhfhg"],["lqglykvsxhobqrppeqrlp"],["hnjctughrsdiyezcqsmij"],["akpellndulbbbipbvatbu"],["uimwaktcywogwptihvrrh"],["izeqjoftsfzjkujiubkrb"],["jcyfpawtcnuikudwuijpd"],["njwftpurketzvjbzivanz"],["mnwjytgktowostuzvrcjxr"],["vyjfniqjoepdbzulvpgjic"],["husuheaiirzowtiadgtxwf","kxntnopkkjgliltrlklfgc"],["fusfadhqfruriiglvqzuns"],["vqcxxbcumypdbetrknavgm"],["daxzqsdcfuymlyevyfnayb"],["azwaipyqlmgoeslujdkwuh"],["othjqfpysicbdhfezxpvhjd"],["cmozvlftrhtxmjqkorxfrql"],["nbyvnbhjlofqdtilvplcdks"],["qmolgaezbwuodbdhsxclhzi"],["pqgkqrancnwaqrjovjlgqsfx"],["sghqrdaelollqmczagojceys"],["kzxlrqbabvtvkfajbjatzyix"],["cwciqqpbmzzcgmnrvgucezor","cwygpjjmrmslabafcmwdhpdo"]]

expected: [["h","k","r","r","t"],["azwaipyqlmgoeslujdkwuh"],["giavjwaftarskv"],["izeqjoftsfzjkujiubkrb"],["aufkyfjuruaq"],["jhujjiiovhw"],["lxtoignhwtcbsi"],["xzv"],["yzksz"],["etus"],["jcyfpawtcnuikudwuijpd"],["lvej"],["olnrizftjnjixeysi"],["varaxwjxf"],["qmiajlowymr"],["gn"],["fjktj"],["cmozvlftrhtxmjqkorxfrql"],["sosnjvqikiivlighyktd"],["nikwaflxpepnkz"],["ivfnyhqqnjdmdwqslhk"],["khugdmdbbqjbeuxq"],["nrlalrdjqqckogfqlhfhg"],["nxmyafxvrfhbuzpzixt"],["quvi"],["swtja"],["qtrbilvqvy"],["wsbvir"],["sanouetznnk"],["tttwsszaetyzgsaprv"],["omuucd"],["yfazdiayalzrnf"],["pvqdzzwv"],["vyjfniqjoepdbzulvpgjic"],["cwygpjjmrmslabafcmwdhpdo"],["pbxvdoleubrdd"],["nzypfebzbsaakoky"],["azlrmjwmlsglgwrdakgn"],["cwciqqpbmzzcgmnrvgucezor"],["uplapswlksu"],["nwcraujocpk"],["nmgwkocmeezb"],["xmlmolj"],["izk"],["cwdqxivcxeyzhsvqccy"],["ywuytvrproahtgro"],["husuheaiirzowtiadgtxwf"],["vqcxxbcumypdbetrknavgm"],["othjqfpysicbdhfezxpvhjd"],["eulboowdyd"],["truufmplrmsxgvrtl"],["pgc"],["yuabbnxybbpfgblou"],["jnyibizgmwjqjvhbg"],["etcnjqg"],["pqgkqrancnwaqrjovjlgqsfx"],["ognmihotoqgprvbt"],["jjgcsekxxi"],["xdhbxxxomhagohdvdyv"],["sghqrdaelollqmczagojceys"],["qmylnzkhz"],["dhvqyqvnh"],["jxklqfdizkgzusrzs"],["lwv"],["ha","ng"],["kzxlrqbabvtvkfajbjatzyix"],["rspgmumnbrzk"],["jcxq"],["xiznzqqjbetchvhndzz"],["cevzkpfcbviliulexyx"],["ligpithabxjqtuaf"],["bogjahrw"],["pfqeu"],["rlzjrirwfhwdvolixa"],["cycu"],["eujibxcxetdjztn"],["yvwfcproumulvnbva"],["jlnlqzviffdmegnxig"],["cf"],["psmqmdceprjoiw"],["ddjikfsnasyj"],["yo"],["nmitv"],["njwftpurketzvjbzivanz"],["jgxxttnlhez"],["mvbwfqqbeisdsjdnn"],["fbwkolpka"],["hnjctughrsdiyezcqsmij"],["rrrkddajfq"],["dneng"],["smavxt"],["ddvxhgesuenqdgutm"],["tvpawacxepvq"],["yjyawflsvetbdpcgbjta"],["nbyvnbhjlofqdtilvplcdks"],["mnwjytgktowostuzvrcjxr"],["vlmkkilhsqlknvqpus"],["ajhaejn"],["tvhmtraayghfabutim"],["jubooimlfis"],["vpnmjbnkf"],["xzzqnowcyplkdxgkbbb"],["itle"],["vnicvmnfwwwmzhsdsm"],["mz"],["nll"],["tqxiqlqkxbmwuytempvg"],["gccpj"],["qmolgaezbwuodbdhsxclhzi"],["tpalgbgirzrl"],["uaduv"],["lzefktml"],["kxntnopkkjgliltrlklfgc"],["oauvt"],["dwzuyrospzjzuckk"],["lqglykvsxhobqrppeqrlp"],["daxzqsdcfuymlyevyfnayb"],["yihridsxajkiyehmdbru"],["cno"],["kcuxsetkmzkq"],["mmncorzbnoawyo"],["ohkaajphvrorgyx"],["rjnvgxk"],["gqkdxbkylirxxqrhh"],["jgbj"],["oc"],["uimwaktcywogwptihvrrh"],["akpellndulbbbipbvatbu"],["nskgjmut"],["fusfadhqfruriiglvqzuns"],["nhasjwodqyququhhfkyv"],["trlhxmqayeiero"],["qmbkbjpkxzmnwvo"],["scruzaydxrapcuv"],["rulvjpezzonnbr"]]

*/