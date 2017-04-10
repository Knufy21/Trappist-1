#include <Trappist-1\animation\AnimationSheet.hpp>

#include <fstream>
#include <sstream>

bool AnimationSheet::load(TextureManager::TextureHandle handle, const std::string &fileName)
{
	this->textureHandle = handle;

	std::ifstream file(fileName/* + ANIMATION_SHEET_INFO_FILE_EXTENSION*/);

	if (!file.good())
		return false;

	std::string line;
	std::string path(fileName.substr(0, fileName.find_last_of('/')));

	// Load texture
	std::getline(file, line);
	TextureManager::load(handle, (path + '/' + line.substr(0, line.size() - 4)).c_str());
	TextureManager::get(handle)->setSmooth(false);

	std::getline(file, line, 'x');
	frameSize.x = std::stof(line);
	std::getline(file, line);
	frameSize.y = std::stof(line);
	
	unsigned int lineNum;
	for (lineNum = 0; std::getline(file, line); ++lineNum)
	{
		std::string lineName;
		std::stringstream splitArg(line);
		std::string splitResult;
		unsigned int num1, num2;
		float num3;
		bool b1, b2, b3, b4;

		//Splits <NAME>:A-B-C-D-E-F-G
		if (std::getline(splitArg, splitResult, ':'))
		{
			lineName = splitResult;
			//Splits NAME:<A-B-C-D-E-F-G>
			if (std::getline(splitArg, splitResult, ':'))
			{
				splitArg = std::stringstream(splitResult);
				//Splits NAME:<A>-B-C-D-E-F-G
				if (std::getline(splitArg, splitResult, '-'))
				{
					num1 = std::stoul(splitResult);
					//Splits NAME:A-<B>-C-D-E-F-G
					if (std::getline(splitArg, splitResult, '-'))
					{
						num2 = std::stoul(splitResult);
						//Splits NAME:A-B-<C>-D-E-F-G
						if (std::getline(splitArg, splitResult, '-'))
						{
							num3 = std::stof(splitResult);
							//Splits NAME:A-B-C-<D>-E-F-G
							if (std::getline(splitArg, splitResult, '-'))
							{
								b1 = std::stoi(splitResult);
								//Splits NAME:A-B-C-D-<E>-F-G
								if (std::getline(splitArg, splitResult, '-'))
								{
									b2 = std::stoi(splitResult);
									//Splits NAME:A-B-C-D-E-<F>-G
									if (std::getline(splitArg, splitResult, '-'))
									{
										b3 = std::stoi(splitResult);
										//Splits NAME:A-B-C-D-E-F-<G>
										if (std::getline(splitArg, splitResult, '-'))
										{
											b4 = std::stoi(splitResult);
											goto ReadWithoutError;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		return false;

	ReadWithoutError:
		auto &animation = animations[lineName];
		animation.startState = num1;
		animation.endState = num2;
		animation.frameTime = num3;
		animation.bools.set(Animation::BOOL_ARRAY_IS_FLIPPED_HORIZONTALLY, b1);
		animation.bools.set(Animation::BOOL_ARRAY_IS_FLIPPED_VERTICALLY, b2);
		animation.bools.set(Animation::BOOL_ARRAY_IS_SMOOTH, b3);
		animation.bools.set(Animation::BOOL_ARRAY_IS_REVERSE, b4);
	}

	file.close();

	return true;
}

const Animation *AnimationSheet::getAnimationByName(const std::string &animationName) const
{
	auto &it = animations.find(animationName);
	if (it != animations.end())
		return &(it->second);
	return nullptr;
}

FloatRect AnimationSheet::getTextureRectByState(Animation::state_t state) const
{
	float x, y;
	Animation::state_t verticalSpriteCount;
	verticalSpriteCount = getTexture()->getSize().x / frameSize.x;
	x = static_cast<float>(state % verticalSpriteCount) * frameSize.x;
	y = static_cast<float>(state / verticalSpriteCount) * frameSize.y;
	return FloatRect(x / getTexture()->getSize().x, y / getTexture()->getSize().y,
		frameSize.x / getTexture()->getSize().x, frameSize.y / getTexture()->getSize().y);
}