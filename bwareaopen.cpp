void bwareaopen(Mat &data, int n)
{
	Mat labels, stats, centroids;
	connectedComponentsWithStats(data, labels, stats, centroids, 8, CV_16U);
	int regions_count = stats.rows - 1;
	int regions_size, regions_x1, regions_y1, regions_x2, regions_y2;

	for (int i = 1; i <= regions_count; i++)
	{
		regions_size = stats.ptr<int>(i)[4];
		if (regions_size < n)
		{
			regions_x1 = stats.ptr<int>(i)[0];
			regions_y1 = stats.ptr<int>(i)[1];
			regions_x2 = regions_x1 + stats.ptr<int>(i)[2];
			regions_y2 = regions_y1 + stats.ptr<int>(i)[3];

			for (int j = regions_y1; j<regions_y2; j++)
			{
				for (int k = regions_x1; k<regions_x2; k++)
				{
					if (labels.ptr<ushort>(j)[k] == i)
						data.ptr<uchar>(j)[k] = 0;
				}
			}
		}
	}
}
