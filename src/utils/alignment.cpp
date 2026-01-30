#include <iostream>
#include <vector>
#include <string>

using namespace std;

int compare_directions(int top, int left, int diagonal, int gap, int mismatch, int match, bool is_match){
	int result;
	int top_acc, left_acc, diagonal_acc;

	top_acc = top + gap;
	left_acc = left + gap;
	if (is_match)
		diagonal_acc = diagonal + match;
	else
		diagonal_acc = diagonal + mismatch;

	if (top_acc < left_acc && top_acc < diagonal_acc)
		result = top_acc;
	else if (left_acc < top_acc && left_acc < diagonal_acc)
		result = left_acc;
	else
		result = diagonal_acc;
		
	return result;
}

vector<int> space_efficient_alignment(string X, string Y, int gap, int mismatch, int match, vector<vector<int>> m){
    int top, left, diagonal;
    int match, mismatch;
    bool is_match;
    int xAxis = X.length() + 1;
    for(int i = 1; i < xAxis; i++){
        top = m[i-1][1];
        left = m[i][0];
        diagonal = m[i-1][0];
        m[i][1] = compare_directions(top, left, diagonal, gap, mismatch, match, is_match);
    }

}