#pragma once

//namespace
//{
	struct KerningInfo
	{
		float amount;
	};

	struct Kerning
	{
		unsigned short ascii1;
		unsigned short ascii2;
		KerningInfo info;
	};
//}