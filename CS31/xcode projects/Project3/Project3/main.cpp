#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//*************************************
//  isValidUppercaseStateCode
//*************************************

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NJ.NH.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

int string_to_integer(string s){
    const int BASE = 10;
    
    int multiplier = 1;
    int rtn = 0;
    
    //traverse string backwards
    for (string::size_type i = s.size(); i > 0; i--){
        //since digits are sequential, 'n' - '0' = n as integer
        int digit = s.at(i - 1) - '0';
        rtn += digit * multiplier;
        
        //for base 10, each digit is x10 the previous digit
        multiplier *= BASE;
    }
    
    return rtn;
}

bool hasRightSyntax(string pollData){
    const int PREDICTION_MIN_LENGTH = 4;
    
    //convert all lowercase in poll data string to uppercase
    for (int k = 0; k < pollData.length(); k++){
        pollData.at(k) = toupper(pollData.at(k));
    }
    
    int i = 0; //index in poll data string
    
    while (i < pollData.length()){
        //next state prediction should have at least 4 characters
        //party code (1) + digit (1) + state code (2) = 4
        if (pollData.length() - i < PREDICTION_MIN_LENGTH) return false;
        
        //party code should be letter
        if (!isalpha(pollData.at(i))) return false;
        i++;
    
        //next one or two characters should be digits
        if (!isdigit(pollData.at(i))) return false;
        i++;
    
        if (isdigit(pollData.at(i))) i++; //if 2-digit number advance again
            
        //should be 2-char state code
        if (!isValidUppercaseStateCode(pollData.substr(i, 2))) return false;
        
        i+=2; //proceed to next state predicition
    }
    return true;
}

int computeVotes(string pollData, char party, int& voteCount){
    if (!hasRightSyntax(pollData)) return 1;
    
    if (!isalpha(party)) return 3;
    
    //convert all lowercase in pollData to uppercase
    for (int k = 0; k < pollData.length(); k++){
        pollData.at(k) = toupper(pollData.at(k));
    }
    
    //convert party to uppercase
    party = toupper(party);
    
    //if a prediciton has zero votes reset voteCount
    int initial_votecount = voteCount;
    //now set the vote count to zero
    voteCount = 0;
    
    int i = 0;
    
    while (i < pollData.length()){
        bool selected_party = false;
        
        if (pollData.at(i) == party) selected_party = true;
        i++;
        
        int count;
        if (isdigit(pollData.at(i + 1))){
            count = string_to_integer(pollData.substr(i, 2));
            i += 2;
        } else {
            count = string_to_integer(pollData.substr(i, 1));
            i++;
        }
        
        if (count == 0){
            voteCount = initial_votecount;
            return 2;
        }
        
        if (selected_party){
            voteCount += count;
        }
            
        i+=2; //proceed to next chunk (skip state code)
    }
    
    return 0;
}

int main(){
}
