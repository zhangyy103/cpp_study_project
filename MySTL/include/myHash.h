#pragma once
#include<unordered_map>
#include<vector>
#include <algorithm>
#include <unordered_set>
#include <string>
using namespace std;

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> hash;
    for (int i = 0; i < nums.size(); i++) {
        auto it = hash.find(target - nums[i]); 
        if (it != hash.end()) {
            return { i, it->second };
        }
        hash[nums[i]] = i;
    }
    return {};
}

std::vector<vector<string>> groupAnagrams(std::vector<string>& strs) {
    std::vector<vector<string>>ans;
    std::unordered_map<string, vector<string>> groupMap;
    for (string str : strs) {
        string temp = str;
        std::sort(temp.begin(), temp.end());
        groupMap[temp].push_back(str);
    }
    for (auto it = groupMap.begin();it != groupMap.end();it++) {
        ans.push_back(it->second);
    }
    return ans;
}

int longestConsecutive(vector<int>& nums) {
    std::unordered_set<int> hash;
    for (auto num : nums) hash.insert(num);    //放入hash表中
    int res = 0;
    for (auto beg : hash) {
        if (!hash.count(beg - 1)) {//如果当前数字x减1不在哈希表中，说明x是连续序列的第一个数字
            int end = beg;   //以当前数x向后枚举
            while (hash.count(end + 1)) end++;
            res = std::max(res, end - beg + 1);  //更新答案
        }
    }
    return res;
}