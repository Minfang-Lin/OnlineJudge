#include <cstdio>
#include <algorithm>

/* 算法一 */ 
int MaxSubseqSum1 (int arr[], int n) {
	int thisSum, maxSum = 0;
	for (int i=0; i<n; ++i) {		
		for (int j=i; j<n; ++j) {
			thisSum = 0;
			for (int k=i; k<j; ++k) {
				thisSum += arr[k];
			}
			if (thisSum > maxSum) {
				maxSum = thisSum;
			}
		}
	}
	return maxSum;
}

/* 算法二 */ 
int MaxSubseqSum2 (int arr[], int n) {
	int thisSum, maxSum = 0;
	for (int i=0; i<n; ++i) {	
		thisSum = 0;	
		for (int j=i; j<n; ++j) {
			thisSum += arr[j];
			if (thisSum > maxSum) {
				maxSum = thisSum;
			}			
		}
	}
	return maxSum;
}

/* 算法三 - 分而治之 */ 
int DivideAndConquer (int arr[], int left, int right) {
	if (left == right) {
		if (arr[left]>0) {
			return arr[left];
		} else {
			return 0;
		}
	}
	
	int center = (left + right) / 2;
	int maxLeftSum = DivideAndConquer(arr, left, center);
	int maxRightSum = DivideAndConquer(arr, center+1, right);
	
	// 从中间往左扫描 
	int maxLeftBoardSum = 0, leftBoardSum = 0;
	for (int i=center; i>=left; --i) {
		leftBoardSum += arr[i];
		if (leftBoardSum > maxLeftBoardSum) {
			maxLeftBoardSum = leftBoardSum;
		}
	}
	
	int maxRightBoardSum = 0, rightBoardSum = 0;
	for (int i=center+1; i<=right; ++i) {
		rightBoardSum += arr[i];
		if (rightBoardSum > maxRightBoardSum) {
			maxRightBoardSum = rightBoardSum;
		}
	}
	
	return std::max(std::max(maxLeftSum, maxRightSum), maxRightBoardSum + maxLeftBoardSum);
} 

int MaxSubseqSum3 (int arr[], int n) {
	return DivideAndConquer(arr, 0, n-1);
}

/* 算法四 */
int MaxSubseqSum4 (int arr[], int n) {
	int thisSum = 0, maxSum = 0;
	for (int i=0; i<n; ++i) {
		thisSum += arr[i];
		if (thisSum > maxSum) {
			maxSum = thisSum;
		}
		if (thisSum < 0)  thisSum = 0;
	} 
	return maxSum; 
}

int main() {
	int n;
	scanf("%d", &n);
	int arr[n];
	for (int i=0; i<n; ++i) {
		scanf("%d", arr+i);
	}
	printf("%d\n", MaxSubseqSum4(arr, n));
	return 0;
} 
