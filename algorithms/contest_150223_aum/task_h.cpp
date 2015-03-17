#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <iterator>
#include <algorithm>

const int UniqueSymbols = 256;
typedef std::vector<bool> HuffCode;
typedef std::map<char, HuffCode> huff_code_map;

class inode
{
public:
    const int f;

    virtual ~inode() {}

protected:
    inode(int f) : f(f) {}
};

class InternalNode : public inode
{
public:
    inode *const left;
    inode *const right;

    InternalNode(inode * c0, inode * c1) : inode(c0->f + c1->f), left(c0), right(c1) {}
    ~InternalNode()
    {
        delete left;
        delete right;
    }
};

class LeafNode : public inode
{
public:
    const char c;

    LeafNode(int frequency, char symbol) : inode(frequency), c(symbol) {}
};

struct NodeCmp
{
    bool operator()(const inode * lhs, const inode * rhs) const { return lhs->f > rhs->f; }
};

inode *build_tree(const int (&frequencies)[UniqueSymbols])
{
    std::priority_queue<inode *, std::vector<inode *>, NodeCmp> trees;

    for (int i = 0; i < UniqueSymbols; ++i)
    {
        if(frequencies[i] != 0)
            trees.push(new LeafNode(frequencies[i], (char)i));
    }

    while (trees.size() > 1)
    {
        inode * childR = trees.top();
        trees.pop();

        inode * childL = trees.top();
        trees.pop();

        inode * parent = new InternalNode(childR, childL);
        trees.push(parent);
    }
    return trees.top();
}

void GenerateCodes(const inode * node, const HuffCode& prefix, huff_code_map & outCodes)
{

    if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
    {
        if(prefix.size()>0)
            outCodes[lf->c] = prefix;
        else{
            HuffCode leftPrefix;
            leftPrefix.push_back(false);
            outCodes[lf->c] = leftPrefix;
        }

    }
    else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
    {
        HuffCode leftPrefix = prefix;
        leftPrefix.push_back(false);
        GenerateCodes(in->left, leftPrefix, outCodes);

        HuffCode rightPrefix = prefix;
        rightPrefix.push_back(true);
        GenerateCodes(in->right, rightPrefix, outCodes);
    }
}
std::vector<bool> encode(std::string& str, huff_code_map& codes){
    std::vector<bool> result;
    for(int i=0;i<str.size();++i){
        std::vector<bool> code = codes[str[i]];
        for(int j=0;j<code.size();++j){
            result.push_back(code[j]);
        }
    }
    return result;
}
int main()
{
    std::ifstream in("encoding.in");
    std::ofstream out("encoding.out");
    // Build frequency table
    int frequencies[UniqueSymbols] = {0};
    std::string sample;
    in>> sample;
    for(int i=0;i<sample.size();i++){
        ++frequencies[sample[i]];
    }

    inode * root = build_tree(frequencies);

    huff_code_map codes;
    GenerateCodes(root, HuffCode(), codes);
    delete root;
    std::vector<bool> result = encode(sample, codes);
    out<<codes.size()<<" "<<result.size()<<std::endl;
    for (huff_code_map::const_iterator it = codes.begin(); it != codes.end(); ++it)
    {
        out << it->first << ": ";
        std::copy(it->second.begin(), it->second.end(),
                std::ostream_iterator<bool>(out));
        out << std::endl;
    }
    std::copy(result.begin(), result.end(),
            std::ostream_iterator<bool>(out));
    out << std::endl;
    return 0;
}