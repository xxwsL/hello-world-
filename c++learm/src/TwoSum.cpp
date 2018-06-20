#include <xxwsL.h>
#include <vector_use.h>

#include<unordered_map>

class Solution {
public:
	//经典算法
	//vector<int> twoSum(vector<int>& nums, int target) {
	//	int num0 = nums.size();
	//	int i, j, temp0;
	//	for (i = 0; i < num0; ++i) {
	//		temp0 = target - nums[i];
	//		for (j = i + 1; j < num0; ++j) {
	//			if (nums[j] == temp0) {
	//				return vector<int> {i,j};
	//			}
	//		}
	//	}
	//}

	//运用map容器升序算法
	vector<int> twoSum(vector<int>& nums, int target){
		unordered_map<int, int> map;
		for (int i = 0; i < nums.size(); i++) {
			//搜索map容器里的键值
			auto it = map.find(target - nums[i]);		
			if (it != map.end()) {
				cout << "map插入数据个数 = "<<map.size() << '\n';
				return { i, it->second };
			}
			map[nums[i]] = i;
		}
		return { 0, 0 };
	}
};

int main(void) 
{
	map<int, int>::value_type (1, 2);
	int buf[10] = { 1,3,3,3,6,6,7,8,9 };
	vector<int> test_buf(buf, buf+sizeof(buf));
	Solution solu;
	printvector(solu.twoSum(test_buf, 9));
	while (1);
	return true;
}