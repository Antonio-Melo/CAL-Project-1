/**
 * File containing all functions related to string matching algorithms and auxiliary functions
 */

#ifndef STRINGSEARCHER_H_
#define STRINGSEARCHER_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

/**
 * Prefix function
 * @param pattern Pattern to process
 * @param prefix Vector to fill with the length of the longest prefix in all indexes of the pattern
 */
void pre_kmp(string pattern, vector<int> & prefix){
	int m=pattern.length();
	prefix[0]=-1;
	int k=-1;
	for (int q=1; q<m; q++) {
		while (k>-1 && pattern[k+1]!=pattern[q])
			k = prefix[k];
		if (pattern[k+1]==pattern[q]) k=k+1;
		prefix[q]=k;
	}
}

/**
 * Knuth-Morris-Pratt implementation to find how many times a pattern occurs in a text
 * @param text Text to find pattern in
 * @param pattern Pattern to search in text
 * @return Number of times pattern appeared in text
 */
int kmp(string text, string pattern){
	int num=0;
	int m=pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n=text.length();

	int q=-1;
	for (int i=0; i<n; i++) {
		while (q>-1 && pattern[q+1]!=text[i])
			q=prefix[q];
		if (pattern[q+1]==text[i])
			q++;
		if (q==m-1) {
			//cout <<"pattern occurs with shift" << i-m+1 << endl;
			num++;
			q=prefix[q];
		}
	}
	return num;
}

/**
 * Exact string search in a vector of strings
 * @param toSearch String to be searched
 * @param text Vector of strings to find toSearch pattern
 * @return Vector sorted by number of times toSearch appeared
 */
vector<string> exactStringSearch(string toSearch, vector<string> text){
	vector<string> tmp;

	for(int i = 0; i < text.size(); i++){
		if (kmp(text[i],toSearch) > 0){
			tmp.push_back(text[i]);
		}
	}

	sort( tmp.begin(), tmp.end() );
	tmp.erase( unique( tmp.begin(), tmp.end() ), tmp.end() );
	return tmp;
}

/**
 * Exact string search in a vector of strings
 * @param toSearch String to be searched
 * @param roads Map of roads to be used by streetmap raw
 * @return Vector sorted by number of times toSearch appeared
 */
vector<string> exactStringSearch(string toSearch, map<int,Road> roads){
	vector<string> tmp;
		map<int, Road>::iterator it = roads.begin();
		map<int, Road>::iterator ite = roads.end();

		while(it != ite){
			tmp.push_back(it->second.getName());
			it++;
		}
		return exactStringSearch(toSearch,tmp);
}

/**
 * EditDistance implementation to find minimum edit distance
 * @param pattern Pattern to search in text
 * @param text Text to find pattern in
 * @return Number of edit operations to transform pattern into text
 */
int editDistance(string pattern, string text){
	int n=text.length();
	vector<int> d(n+1);
	int old,neww;
	for (int j=0; j<=n; j++)
		d[j]=j;
	int m=pattern.length();
	for (int i=1; i<=m; i++) {
		old = d[0];
		d[0]=i;
		for (int j=1; j<=n; j++) {
			if (pattern[i-1]==text[j-1]) neww = old;
			else {
				neww = min(old,d[j]);
				neww = min(neww,d[j-1]);
				neww = neww +1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

/**
 * Approximate string search in a vector of strings
 * @param toSearch String to be searched
 * @param text Vector of strings to find toSearch pattern
 * @return Vector sorted by number of times toSearch appeared
 */
vector<string> approximateStringSearch(string toSearch, vector<string> text){
	multimap<float, string> tmp;

	for(int i = 0; i < text.size(); i++){
		tmp.insert(pair<float,string>((float) ((float)editDistance(toSearch,text[i]) / (text[i].size() + toSearch.size())), text[i]));
	}

	vector <string> results;

	multimap<float, string>::iterator itr = tmp.begin();
	multimap<float, string>::iterator itre = tmp.end();

	for( itr; itr != itre; itr++) {
		//evitar nomes de ruas repetidos
		if(results.size() > 0 ){
			if (results[results.size() - 1] != itr->second){
				results.push_back( itr->second );
			}
		} else {
			results.push_back( itr->second );
		}
		//cout << itr->first << " - "<< itr->second << endl;
	}

	return results;
}

/**
 * Approximate string search in a vector of strings
 * @param toSearch String to be searched
 * @param roads Map of roads to be used by streetmap raw
 * @return Vector sorted by number of times toSearch appeared
 */
vector<string> approximateStringSearch(string toSearch, map<int,Road> roads){
	vector<string> tmp;
	map<int, Road>::iterator it = roads.begin();
	map<int, Road>::iterator ite = roads.end();

	while(it != ite){
		tmp.push_back(it->second.getName());
		it++;
	}
	return approximateStringSearch(toSearch,tmp);
}

#endif
