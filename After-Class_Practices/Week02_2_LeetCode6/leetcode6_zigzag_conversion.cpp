// Not best solution
class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows==1)
            return s;
        int diff=(numRows)*2-2;
        string ans="";
        for(int row=0;row<numRows;row++)
        {
            bool flag=false;
            for(int j=row;j<s.length();flag=!flag)
            {
                ans=ans+s[j];
                if(row==0||row==numRows-1)
                	j+=diff;
                else if(flag)
                    j+=row*2;
                else
                    j+=(diff-row*2);
            }
        }
        return ans;
    }
};