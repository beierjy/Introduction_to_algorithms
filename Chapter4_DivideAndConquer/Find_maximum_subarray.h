//Ѱ����������飬�����Խ�е�����ĺ͵Ĵ�С

//��Խ�е㣬����������ֵ
template <typename Type>
Type find_max_crossing_subarray(Type a[],int &low, int mid, int &high)
{
	Type left_sum = -999999999;
	Type sum = 0;
	int max_left, max_right;
	for (int i = mid; i >= low; i--)//����������������Ļ������޷���i�Ƚϵõ���ȷ�ıȽϽ������Ϊһ���������� ����ɲ���
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

//��������

template <typename Type>

Type find_maxmum_subarray(Type a[], int &low, int &high)//�����������������������������ֵ
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
		left_low = low; left_high = mid;//�������ʹ����ʱ�ı��� ����ı���ԭ����ֵ���޷�����������ȥ
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