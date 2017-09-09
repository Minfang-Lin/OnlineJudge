#include <cstdio>

int main() {
	int n;
	scanf("%d", &n);
	int arr[n];
	for (int i=0; i<n; ++i) {
		scanf("%d", arr+i);
	}
	
	int left = 0, right = 0, maxSum = 0, start = arr[0], thisSum = 0;
	bool flag = false; // 是否出现过非负数
	for (int i=0; i<n; ++i) {
		thisSum += arr[i];
		if (arr[i] >= 0) 
			flag = true;
		if (thisSum > maxSum) {
			maxSum = thisSum;
			left = start;
			right = arr[i];
			flag = true;
		}
		if (thisSum < 0) {
			thisSum = 0;
			if (i<n-1) {
				start = arr[i+1];
			}
		}
	}
	
	if (flag) printf("%d %d %d\n", maxSum, left, right);
	else printf("%d %d %d\n", maxSum, arr[0], arr[n-1]);
	return 0;
}
