#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class HuffmanTree {
	string text;
	struct Node {
		char ch;
		int freq;
		Node* left, * right;
	};

public:
	HuffmanTree(string ntext) {
		text = ntext;
	}

	Node* getNode(char ch, int freq, Node* left, Node* right) {
		Node* node = new Node();
		node->ch = ch;
		node->freq = freq;
		node->left = left;
		node->right = right;

		return node;
	}

	struct comp {
		bool operator()(Node* l, Node* r) {
			return l->freq > r->freq;
		}
	};

	void encode(Node* root, string str, unordered_map<char, string>& huffmancode) {
		if (root == nullptr) {
			return;
		}
		if (!root->left && !root->right) {
			huffmancode[root->ch] = str;
		}
		encode(root->left, str + '0', huffmancode);
		encode(root->right, str + '1', huffmancode);
	}

	void decode(Node* root, int& id, string str) {
		if (root == nullptr) {
			return;
		}

		if (!root->left && !root->right) {
			cout << root->ch;
			return;
		}

		id++;

		if (str[id] == '0') {
			decode(root->left, id, str);
		}
		else {
			decode(root->right, id, str);
		}
	}

	void buildHuffmanTree() {
		unordered_map<char, int> freq;
		for (char ch : text) {
			freq[ch]++;
		}

		priority_queue<Node*, vector<Node*>, comp> pq;

		for (auto& pair : freq) {
			pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
		}

		while (pq.size() != 1) {
			Node* left = pq.top(); pq.pop();
			Node* right = pq.top();	pq.pop();

			int sum = left->freq + right->freq;
			pq.push(getNode('\0', sum, left, right));
		}

		Node* root = pq.top();
		unordered_map<char, string> huffmanCode;
		encode(root, "", huffmanCode);

		cout << "Huffman Codes are :\n" << '\n';
		for (auto& pair : huffmanCode) {
			cout << pair.first << " " << freq[pair.first] << " " << pair.second << '\n';
		}

		cout << "\nOriginal string was :\n" << text << '\n';

		string str = "";
		for (char ch : text) {
			str += huffmanCode[ch];
		}

		cout << "\nEncoded string is :\n" << str << '\n';

		int id = -1;
		cout << "\nDecoded string is: \n";
		while (id < (int)str.size() - 2) {
			decode(root, id, str);
		}
	}
};

int main()
{
	HuffmanTree text("The best in St. Petersburg State University  - faculty of PM-PU.");

	text.buildHuffmanTree();

	return 0;
}