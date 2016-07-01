//寻找最大子数组，求出跨越中点数组的和的大小

//跨越中点，求数组的最大值
template <typename Type>
Type find_max_crossing_subarray(Type a[],int &low, int mid, int &high)
{
	Type left_sum = -999999999;
	Type sum = 0;
	int max_left, max_right;
	for (int i = mid; i >= low; i--)//这里如果用正整数的话，将无法和i比较得到正确的比较结果，因为一旦减到负数 将变成补数
	{
		sum = sum + a[i];
		if (sum > left_sum){
			left_sum = sum;
			max_left = i;
		}
	}
	low = max_left;
	Type right_sum = -9999999999;
	sum = 0;
	for (int i = mid + 1; i <= high; ++i)
	{
		sum =sum + a[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = i;
		}
	}
	high = max_right;
	return left_sum + right_sum;
}

//划分数组

template <typename Type>

Type find_maxmum_subarray(Type a[], int &low, int &high)//利用引用来返回另外的两个参数的值
{
	int left_low, left_high, right_low, right_high;
	Type left_sum, right_sum, cross_sum;
	if (high == low)
	{
		return a[low];
	}
	else
	{
		int mid = (high + low) / 2;
		left_low = low; left_high = mid;//这里必须使用临时的变量 否则改变了原来的值将无法继续迭代下去
		right_high = high; right_low = mid + 1;
		left_sum = find_maxmum_subarray(a, left_low, left_high);
		right_sum = find_maxmum_subarray(a, right_low, right_high);
		cross_sum = find_max_crossing_subarray(a, low, mid, high);
	}
	if (left_sum >= right_sum && left_sum >= cross_sum)
	{
		low = left_low; high = left_high;
		return  left_sum;
	}
	else if (right_sum >= left_sum && right_sum >= cross_sum)
	{
		low = right_low; high = right_high;
		return right_sum;
	}
	else
		return cross_sum;
		
}