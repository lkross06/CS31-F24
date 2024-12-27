#include <iostream>
#include <string>
#include <cassert>
using namespace std;

/*
 ===========================
 NOT REQUIRED FOR SUBMISSION
 ===========================
 prints out the array in order of its elements, separated by ", ".
 */
void printArray(string a[], int n){
    for (int i = 0; i < n; i++){
        cout << a[i];
        if (i != n - 1) cout << ", ";
    }
    cout << endl;
}

/*
 ===========================
 NOT REQUIRED FOR SUBMISSION
 ===========================
 prints out a separator in the terminal (assumes the last thing printed was endl).
 */
void printSep(){
    cout << "====================" << endl;
}

/*
 ===========================
 HELPER FUNCTION
 ===========================
 Eliminate the item at position pos by copying all elements before it one place to the right. Put the item that was thus eliminated into the first position of the array. Return the original position of the item that was moved to the beginning.
 */
int rotateRight(string a[], int n, int pos){
    if (n < 0) return -1; //bad argument
    if (pos < 0 || pos >= n) return -1; //bad argument
    
    string temp = a[pos];
    
    //traverse every element before pos but backwards (so that every value is preserved)
    for (int i = pos; i > 0; i--){
        //will not cause undefined behavior because i is never <= 0 or > n
        //(see restrictions on pos above)
        a[i] = a[i-1];
    }
    
    a[0] = temp; //now copy the pos-th element into the last position
    
    return pos;
}

/*
 Append value to the end of each of the n elements of the array and return n
 */
int appendToAll(string a[], int n, string value){
    if (n < 0) return -1; //bad argument
    
    for (int i = 0; i < n; i++){
        a[i] += value;
    }
    
    return n;
}

/*
 Return the position of a string in the array that is equal to target; if there is more than one such string, return the smallest position number of such a matching string. Return −1 if there is no such string.
 */
int lookup(const string a[], int n, string target){
    if (n < 0) return -1; //bad argument
    
    int i = 0;
    while (a[i] != target && i < n) i++;
    
    if (i == n) return -1; //(i < n) == false, so target not found
    
    return i; //(a[i] != target) == false, so first found target is at index i
    
}

/*
 Return the position of a string in the array such that that string is >= every string in the array. If there is more than one such string, return the smallest position number of such a string. Return −1 if the function should consider no elements to be part of the array.
 */
int positionOfMax(const string a[], int n){
    if (n <= 0) return -1; //bad argument or empty array
    
    //since the final max should be the smallest position, lets traverse backwards
    int maxPos = n - 1;
    for (int i = n - 2; i >= 0; i--){
        if (a[i] >= a[maxPos]) maxPos = i;
    }
    
    return maxPos;
}

/*
 Eliminate the item at position pos by copying all elements after it one place to the left. Put the item that was thus eliminated into the last position of the array that the function knows about. Return the original position of the item that was moved to the end.
 */
int rotateLeft(string a[], int n, int pos){
    if (n < 0) return -1; //bad argument
    if (pos < 0 || pos >= n) return -1; //bad argument
    
    string temp = a[pos];
    
    //traverse every element after pos
    for (int i = pos + 1; i < n; i++){
        //will not cause undefined behavior because i is never <= 0 or > n
        //(see restrictions on pos above)
        a[i-1] = a[i];
    }
    
    a[n - 1] = temp; //now copy the pos-th element into the last position
    
    return pos;
}

/*
 Return the number of sequences of one or more consecutive identical items in a.
 */
int countRuns(const string a[], int n){
    if (n < 0) return -1; //bad argument
    if (n == 0) return 0; //if theres no elements then theres zero sequences
    
    //since theres at least one element in the array theres at least one sequence
    int numSequences = 1;
    
    for (int i = 0; i < n - 1; i++){
        //if the current item does not equal the next item, then the next sequence has started
        //and we can increment the number of sequences by one
        if (a[i] != a[i + 1]) numSequences++;
    }
    
    return numSequences;
}

/*
 Reverse the order of the elements of the array and return n.
 */
int flip(string a[], int n){
    if (n < 0) return -1; //bad arguments
    
    //if theres an odd length then the middle value does not change, so int division works
    for (int i = 0; i < n / 2; i++){
        //mirror the nth element to the left (index i)
        //and the nth element to the right (index (n - 1) - i)
        string* left = &a[i];
        string* right = &a[(n - 1) - i];
        
        //commence the swap
        string temp = *left; //temp is the value at array index i1
        *left = *right;
        *right = temp;
    }
    
    return n;
}

/*
 Return the position of the first corresponding elements of a1 and a2 that are not equal. n1 is the number of interesting elements in a1, and n2 is the number of interesting elements in a2. If the arrays are equal up to the point where one or both runs out, return whichever value of n1 and n2 is less than or equal to the other.
 */
int differ(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0) return -1; //bad arguments
    
    //shortest length between the two strings
    int minLength = n1;
    if (n2 < n1) minLength = n2;
    
    //we dont need to check anything past the length of the shorter array
    for (int i = 0; i < minLength; i++){
        if (a1[i] != a2[i]) return i;
    }
    
    return minLength;
}

/*
 If all n2 elements of a2 appear in a1, consecutively and in the same order, then return the position in a1 where that subsequence begins. If the subsequence appears more than once in a1, return the smallest such beginning position in the array. Return −1 if a1 does not contain a2 as a contiguous subsequence. (Consider a sequence of 0 elements to be a subsequence of any sequence, even one with no elements, starting at position 0.)
 */
int subsequence(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0) return -1; //bad arguments
    
    if (n2 == 0) return 0; //if theres no elements in the subsequence, it starts at position zero
    if (n2 > n1) return -1; //if subsequence is larger than full sequence, a1 does not contain a2
    
    int n2Position = 0;
    bool checkingN2 = false;
    int checkingStartPos = 0;
    
    for (int i = 0; i < n1; i++){
        if (checkingN2) {
            //if the next item in subsequence matches next item in full sequence increment index
            if (a1[i] == a2[n2Position]) n2Position++;
            //otherwise subsequence is not here, reset to checking start of subsequence
            else checkingN2 = false;
            
            //if the end of the subsequence is successfully reached, return the starting index
            //returning here returns only the smallest beginning position
            if (n2Position == n2) return checkingStartPos;
        }
        
        //second condition makes it so that a new subsequence can be checked immediately
        //after a previous one fails.
        if (a1[i] == a2[0] && !checkingN2) {
            //once start of subsequence is found, start checking for full subsequence
            checkingN2 = true;
            checkingStartPos = i; //index where the subsequence started in full sequence
            n2Position = 1; //so that the next thing checked is the second element
        }
    }
    
    //if nothing is returned by now than theres no subsequence in the full sequence
    return -1;
}

/*
 Return the smallest position in a1 of an element that is equal to any of the n2 elements in a2. Return −1 if no element of a1 is equal to any element of a2.
 */
int lookupAny(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0) return -1; //bad arguments
    
    for (int i = 0; i < n1; i++){ //for every element in a1
        for (int j = 0; j < n2; j++){ //check against every element in a2
            if (a1[i] == a2[j]) return i;
        }
    }
    
    //if nothing returns by here, then there is no match and a1 and a2 are completely distinct
    return -1;
}

/*
 Rearrange the elements of the array so that all the elements whose value is < separator come before all the other elements, and all the elements whose value is > separator come after all the other elements. Return the position of the first element that, after the rearrangement, is not < separator, or n if there are no such elements.
 */
int separate(string a[], int n, string separator){
    if (n < 0) return -1; //bad argument
    
    int notLessCounter = 0; //number of elements >= separator
    int lessCounter = 0; //number of elements < separator
    int i = 0;
    
    //only quit after every element has been seen
    while (lessCounter + notLessCounter < n){
        if (a[i] < separator){
            rotateRight(a, n, i); //move to beginning of array
            i++; //advance to next value
            lessCounter++;
        } else if (a[i] > separator){
            rotateLeft(a, n, i); //move to end of array
            notLessCounter++; //index now holds a new value to analyze
        } else { //separator is in array
            i++; //skip over it
            notLessCounter++;
        }
    }

    return n - notLessCounter;
}

//int main() {
//    string a[6] = {"a", "b", "c", "d", "e", "f"};
//    //test appendToAll() functionality, also see if it returns n on success
//    assert(appendToAll(a, 5, "x") == 5 && a[2] == "cx" && a[4] == "ex");
//    //test appendToAll() handling bad arguments and not changing array
//    assert(appendToAll(a, -12, "y") == -1 && a[0] == "ax" && a[2] == "cx");
//    //test appendToAll() only editing subarray given
//    assert(appendToAll(a, 3, "n") == 3 && a[2] == "cxn" && a[3] == "dx");
//    
//    string b[6] = {"a", "b", "c", "d", "e", "f"};
//    //test lookup() for functionality and case-sensitivity
//    assert(lookup(b, 6, "c") == 2 && lookup(b, 6, "C") == -1);
//    //test lookup() handling bad arguments
//    assert(lookup(b, -22, "a") == -1);
//    //test lookup() handling target not found
//    assert(lookup(b, 2, "d") == -1 && lookup(b, 6, "t") == -1);
//    
//    string c[6] = {"a", "d", "c", "d", "f", "f"};
//    //test positionOfMax() functionality, only finding first occurence, handling zero length array
//    assert(positionOfMax(c, 6) == 4 && positionOfMax(c, 3) == 1 && positionOfMax(c, 0) == -1);
//    //test positionOfMax() handling bad arguments
//    assert(positionOfMax(c, -12) == -1);
//    
//    string d[4] = {"a", "b", "c", "d"};
//    //test rotateLeft() functionality
//    assert(rotateLeft(d, 4, 1) == 1 && d[1] == "c" && d[3] == "b");
//    //test rotateLeft() handling bad arguments and not changing array
//    assert(rotateLeft(d, -11, 0) == -1 && d[1] == "c" && d[3] == "b");
//    
//    string e[5] = {"b", "b", "c", "d", "d"};
//    string f[3] = {"b", "b", "b"};
//    //test countRuns() functionality
//    assert(countRuns(e, 5) == 3 && countRuns(f, 3) == 1 && countRuns(f, 0) == 0);
//    //test countRuns() handling bad arguments
//    assert(countRuns(e, -22) == -1);
//    
//    string g[4] = {"a", "b", "c", "d"};
//    string h[5] = {"a", "b", "c", "d", "e"};
//    //test flip() functionality
//    assert(flip(g, 4) == 4 && g[0] == "d" && g[2] == "b");
//    assert(flip(h, 5) == 5 && h[2] == "c" && h[1] == "d");
//    //test flip() handling bad arguments and not changing array
//    assert(flip(g, -1) == -1 && g[0] == "d");
//    
//    string i[5] = {"a", "b", "c", "e", "d"};
//    string j[4] = {"a", "b", "c", "d"};
//    //test differ() functionality
//    assert(differ(i, 5, j, 4) == 3 && differ(i, 4, j, 3) == 3);
//    //test differ() handling bad arguments
//    assert(differ(i, -2, j, 4) == -1 && differ(i, 3, j, -1) == -1);
//    
//    string k[4] = {"a", "b", "c", "d"};
//    string l[2] = {"c", "d"};
//    //test subsequence() functionality
//    assert(subsequence(k, 4, l, 2) == 2 && subsequence(k, 2, l, 1) == -1);
//    //test subsequence() handling bad arguments
//    assert(subsequence(k, -1, l, 2) == -1 && subsequence(k, 4, l, -2) == -1);
//    
//    string m[4] = {"a", "b", "c", "d"};
//    string n[4] = {"e", "f", "g", "b"};
//    //test lookupAny() functionality
//    assert(lookupAny(m, 4, n, 4) == 1 && lookupAny(m, 4, n, 3) == -1);
//    //test lookupAny() handling bad arguments
//    assert(lookupAny(m, -5, n, 3) == -1 && lookupAny(m, 4, n, -2) == -1);
//    
//    string o[5] = {"e", "a", "d", "c", "b"};
//    string p[4] = {"e", "a", "d", "f"};
//    string q[5] = {"d", "e", "c", "a", "b"};
//    //test separate() functionality
//    assert(separate(o, 5, "c") == 2 && o[1] < "c" && o[3] >= "c");
//    assert(separate(p, 4, "c") == 1 && o[0] < "c" && o[2] >= "c");
//    //test separate() handling bad arguments
//    assert(separate(q, -1, "r") == -1);
//    
//    cout << "success" << endl;
//}

int main()
    {
        string h[7] = { "melania", "kamala", "donald", "tim", "", "doug", "jd" };
        assert(lookup(h, 7, "doug") == 5);
        assert(lookup(h, 7, "donald") == 2);
        assert(lookup(h, 2, "donald") == -1);
        assert(positionOfMax(h, 7) == 3);

        string g[4] = { "melania", "kamala", "jd", "usha" };
        assert(differ(h, 4, g, 4) == 2);
        assert(appendToAll(g, 4, "?") == 4 && g[0] == "melania?" && g[3] == "usha?");
        assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jd?" && g[3] == "kamala?");

        string e[4] = { "donald", "tim", "", "doug" };
        assert(subsequence(h, 7, e, 4) == 2);

        string d[5] = { "kamala", "kamala", "kamala", "tim", "tim" };
        assert(countRuns(d, 5) == 2);
    
        string f[3] = { "jd", "donald", "gwen" };
        assert(lookupAny(h, 7, f, 3) == 2);
        assert(flip(f, 3) == 3 && f[0] == "gwen" && f[2] == "jd");
    
        assert(separate(h, 7, "jd") == 3);
    
        cout << "All tests succeeded" << endl;
    }
