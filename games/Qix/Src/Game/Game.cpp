/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Game.hpp"
#include "../../Include/Enum.hpp"

ar::Qix::Qix() : _manageMap(45, 80), _isPaused(true)
{
	std::srand(std::time(nullptr));

	this->_data = {0, "Unknown", 0};
	this->_spritePath = "./resources/un_seul_etre_vous_manque_et_tout_est_depeuple_qix.png";

	this->_startPause = -1;
	this->_tmpTimer = 0;
	this->_timer = std::time(nullptr);
	this->_time = clock();

	this->_life = 3;
	this->_patternQix = 0;
	this->_listSharks.emplace_back(this->_manageMap, true);
	this->_listSharks.emplace_back(this->_manageMap, false);
	this->_flame = nullptr;

	this->_lastBorderPosX = this->_manageMap._map.getPlayerX();
	this->_lastBorderPosY = this->_manageMap._map.getPlayerY();
	this->_actualDir = DirObj::UNKNOWN;
	this->_isPlayerStopped = false;

	this->_sprites.insert({0, {0, 0, 32, 32}});
	this->_sprites.insert({1, {0, 0, 32, 32}});
	this->_sprites.insert({2, {0, 0, 32, 32}});
	this->_sprites.insert({3, {32, 0, 32, 32}});
	this->_sprites.insert({4, {0, 32, 32, 32}});
	this->_sprites.insert({5, {64, 0, 32, 32}});
	this->_sprites.insert({6, {0, 64, 32, 32}});
	this->_sprites.insert({7, {32, 64, 32, 32}});
	this->_sprites.insert({8, {64, 64, 32, 32}});
	this->_sprites.insert({9, {32, 32, 32, 32}});
	this->_sprites.insert({10, {64, 32, 32, 32}});



	colorVector color = {255, 255, 255};
	this->_colors.insert({0, color});

	color = {0, 0, 0};
	this->_colors.insert({1, color});

	color = {0, 0, 0};
	this->_colors.insert({2, color});

	color = {0, 255, 255};
	this->_colors.insert({3, color});

	color = {0, 0, 0};
	this->_colors.insert({4, color});

	color = {255, 255, 0};
	this->_colors.insert({5, color});

	color = {255, 0, 0};
	this->_colors.insert({6, color});

	color = {0, 0, 0};
	this->_colors.insert({7, color});

	color = {255, 100, 100};
	this->_colors.insert({8, color});

	color = {0, 0, 255};
	this->_colors.insert({9, color});

	color = {255, 0, 255};
	this->_colors.insert({10, color});
}

ar::Qix::~Qix()
{
	if (this->_flame)
		delete this->_flame;
}

void ar::Qix::joinTheBorder(void)
{
	for (int idx = 0; idx < this->_manageMap._map.getWidth(); ++idx) {
		if (GetCharTo(this->_manageMap._map.getPlayerX(), this->_manageMap._map.getPlayerY() + idx) == MapPattern::BORDER) {
			this->_manageMap._map.setPlayerY(this->_manageMap._map.getPlayerY() + idx);
			break;
		}
		if (GetCharTo(this->_manageMap._map.getPlayerX(), this->_manageMap._map.getPlayerY() - idx) == MapPattern::BORDER) {
			this->_manageMap._map.setPlayerY(this->_manageMap._map.getPlayerY() - idx);
			break;
		}
		if (GetCharTo(this->_manageMap._map.getPlayerX() + idx, this->_manageMap._map.getPlayerY()) == MapPattern::BORDER) {
			this->_manageMap._map.setPlayerX(this->_manageMap._map.getPlayerX() + idx);
			break;
		}
		if (GetCharTo(this->_manageMap._map.getPlayerX() - idx, this->_manageMap._map.getPlayerY()) == MapPattern::BORDER) {
			this->_manageMap._map.setPlayerX(this->_manageMap._map.getPlayerX() - idx);
			break;
		}
	}
}

void ar::Qix::loop()
{
	static int lastPosX = 0;
	static int lastPosY = 0;

	if (clock() - _time < 100000 || _isPaused == true)
		return;
	if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] ==
		MapPattern::PLAYER)
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] = this->_behindPlayer;

	if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::OLDBORDER ||
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::NOWALKABLE)
		joinTheBorder();

	movePlayer();

	if (_flame &&
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] !=
			MapPattern::TRAIL) {
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = _flame->getLastChar();
		delete _flame;
		_flame = nullptr;
	}

	for (auto it = this->_listSharks.begin();
		it != this->_listSharks.end(); ++it) {
		if ((*it).loopSharks(this->_manageMap) == 1) {
			this->_life--;
			if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] !=
				MapPattern::BORDER &&
				this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] !=
					MapPattern::SHARKS) {
				this->_manageMap._map.setPlayerY(
					this->_lastBorderPosY);
				this->_manageMap._map.setPlayerX(
					this->_lastBorderPosX);
			}
			resetSpecificCharMap(MapPattern::TRAIL);
		}
	}
	if (_flame && _flame->loopSharks(this->_manageMap) == 1) {
		this->_life--;
		this->_manageMap._map.setPlayerY(this->_lastBorderPosY);
		this->_manageMap._map.setPlayerX(this->_lastBorderPosX);
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = WALKABLE;
		resetSpecificCharMap(MapPattern::TRAIL);
		delete _flame;
		_flame = nullptr;
	}
	if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] !=
		MapPattern::TRAIL)
		fillBox();
	else
		updateMap();
	randomMoveQix();

	if (lastPosX == this->_manageMap._map.getPlayerX() &&
		lastPosY == this->_manageMap._map.getPlayerY() &&
		!this->_flame &&
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] ==
			MapPattern::TRAIL) {
		_flame = new ManageSharks(this->_manageMap, true);
		SetDirFlameToGo();
		_flame->setLastChar(MapPattern::TRAIL);
		this->_manageMap._map[this->_manageMap._map.getHeight() - 1][this->_manageMap._map.getWidth() - 1] =
			MapPattern::BORDER;
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = MapPattern::SHARKS;
	}
	if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] ==
		MapPattern::WALKABLE) {
		this->_manageMap._map.setPlayerY(this->_lastBorderPosY);
		this->_manageMap._map.setPlayerX(this->_lastBorderPosX);
	}
	lastPosX = this->_manageMap._map.getPlayerX();
	lastPosY = this->_manageMap._map.getPlayerY();
	_time = clock();
	updateScore();
}

void ar::Qix::setPause()
{
 	this->_isPaused = true;
}

void ar::Qix::updateScore()
{
	int sizeMob = 64;
	int walkableArea = 0;

	for (int y = 0; y < this->_manageMap._map.getHeight(); ++y) {
		for (int x = 0; x < this->_manageMap._map.getWidth(); ++x) {
			if (this->_manageMap._map[y][x] ==
				MapPattern::WALKABLE ||
				this->_manageMap._map[y][x] ==
					MapPattern::TRAIL)
				walkableArea++;
		}
	}
	float percent = (int)(((float)walkableArea /
		(float)((this->_manageMap._map.getHeight() - 1) *
			(this->_manageMap._map.getWidth() - 1) - sizeMob)) * 100);
	this->_data.score = int((100 - percent) * 100);
}

bool ar::Qix::isGameOver()
{
	int sizeMob = 64;
	int walkableArea = 0;

	if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] ==
		MapPattern::PLAYER)
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] = this->_behindPlayer;
	if (_life <= 0)
		return true;
	for (int y = 0; y < this->_manageMap._map.getHeight(); ++y) {
		for (int x = 0; x < this->_manageMap._map.getWidth(); ++x) {
			if (this->_manageMap._map[y][x] ==
				MapPattern::WALKABLE ||
				this->_manageMap._map[y][x] ==
					MapPattern::TRAIL)
				walkableArea++;
		}
	}
	float percent = (int)(((float)walkableArea /
		(float)((this->_manageMap._map.getHeight() - 1) *
			(this->_manageMap._map.getWidth() - 1) - sizeMob)) * 100);
	if (percent <= 70 && this->_patternQix == 0) {
		this->_listSharks.emplace_back(this->_manageMap, true);
		this->_patternQix = 1;
	} else if (percent <= 45 && this->_patternQix == 1) {
		this->_listSharks.emplace_back(this->_manageMap, false);
		this->_patternQix = 2;
	}
	this->_data.score = int((100 - percent) * 100);

	return (percent <= 25);
}

const std::map<unsigned char, ar::colorVector> &ar::Qix::getColors() const
{
	return this->_colors;
}

ar::Map &ar::Qix::getMap()
{
	_behindPlayer = (MapPattern)(this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()]);
	this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] = MapPattern::PLAYER;
	return this->_manageMap._map;
}

int ar::Qix::GetCharTo(int x, int y)
{
	int result = -1;

	if (x < 0 || y < 0 || x >= this->_manageMap._map.getWidth() || y >= this->_manageMap._map.getHeight())
		return result;
	result = this->_manageMap._map[y][x];
	return result;
}

int ar::Qix::ToUp(int charFrom)
{
	int charTo = GetCharTo(this->_manageMap._map.getPlayerX(), this->_manageMap._map.getPlayerY() - 1);

	if (charTo == MapPattern::QIX)
		return 1;
	if (charTo == -1 || (charTo != MapPattern::WALKABLE && charTo != MapPattern::BORDER))
		return 0;
	if (charTo == MapPattern::WALKABLE) {
		charTo = GetCharTo(this->_manageMap._map.getPlayerX(), this->_manageMap._map.getPlayerY() - 2);
		int charToSharks = GetCharTo(this->_manageMap._map.getPlayerX() - 1, this->_manageMap._map.getPlayerY() - 1);
		int charToSharksbis = GetCharTo(this->_manageMap._map.getPlayerX() + 1, this->_manageMap._map.getPlayerY() - 1);
		if (charTo == MapPattern::TRAIL || charTo == MapPattern::SHARKS ||
			charToSharks == MapPattern::TRAIL || charToSharks == MapPattern::SHARKS ||
			charToSharksbis == MapPattern::TRAIL || charToSharksbis == MapPattern::SHARKS)
			return 0;
		this->_manageMap._map[this->_manageMap._map.getPlayerY() - 1][this->_manageMap._map.getPlayerX()] = MapPattern::TRAIL;
		if (charFrom == MapPattern::BORDER) {
			this->_lastBorderPosX = this->_manageMap._map.getPlayerX();
			this->_lastBorderPosY= this->_manageMap._map.getPlayerY();
		}
	} else if (charTo == MapPattern::BORDER && charFrom == MapPattern::TRAIL) {
		fillBox();
	}
	this->_manageMap._map.setPlayerY(this->_manageMap._map.getPlayerY() - 1);
	return 0;
}

int ar::Qix::ToDown(int charFrom)
{
	int charTo = GetCharTo(this->_manageMap._map.getPlayerX(), this->_manageMap._map.getPlayerY() + 1);

	if (charTo == MapPattern::QIX)
		return 1;
	if (charTo == -1 || (charTo != MapPattern::WALKABLE && charTo != MapPattern::BORDER))
		return 0;
	if (charTo == MapPattern::WALKABLE) {
		charTo = GetCharTo(this->_manageMap._map.getPlayerX(), this->_manageMap._map.getPlayerY() + 2);
		int charToSharks = GetCharTo(this->_manageMap._map.getPlayerX() - 1, this->_manageMap._map.getPlayerY() + 1);
		int charToSharksbis = GetCharTo(this->_manageMap._map.getPlayerX() + 1, this->_manageMap._map.getPlayerY() + 1);
		if (charTo == MapPattern::TRAIL || charTo == MapPattern::SHARKS ||
			charToSharks == MapPattern::TRAIL || charToSharks == MapPattern::SHARKS ||
			charToSharksbis == MapPattern::TRAIL || charToSharksbis == MapPattern::SHARKS)
			return 0;
		this->_manageMap._map[this->_manageMap._map.getPlayerY() + 1][this->_manageMap._map.getPlayerX()] = MapPattern::TRAIL;
		if (charFrom == MapPattern::BORDER) {
			this->_lastBorderPosX = this->_manageMap._map.getPlayerX();
			this->_lastBorderPosY= this->_manageMap._map.getPlayerY();
		}
	} else if (charTo == MapPattern::BORDER && charFrom == MapPattern::TRAIL) {
		fillBox();
	}
	this->_manageMap._map.setPlayerY(this->_manageMap._map.getPlayerY() + 1);
	return 0;
}

int ar::Qix::ToLeft(int charFrom)
{
	int charTo = GetCharTo(this->_manageMap._map.getPlayerX() - 1, this->_manageMap._map.getPlayerY());

	if (charTo == MapPattern::QIX)
		return 1;
	if (charTo == -1 || (charTo != MapPattern::WALKABLE && charTo != MapPattern::BORDER))
		return 0;
	if (charTo == MapPattern::WALKABLE) {
		charTo = GetCharTo(this->_manageMap._map.getPlayerX() - 2, this->_manageMap._map.getPlayerY());
		int charToSharks = GetCharTo(this->_manageMap._map.getPlayerX() - 1, this->_manageMap._map.getPlayerY() + 1);
		int charToSharksbis = GetCharTo(this->_manageMap._map.getPlayerX() - 1, this->_manageMap._map.getPlayerY() - 1);
		if (charTo == MapPattern::TRAIL || charTo == MapPattern::SHARKS ||
			charToSharks == MapPattern::TRAIL || charToSharks == MapPattern::SHARKS ||
			charToSharksbis == MapPattern::TRAIL || charToSharksbis == MapPattern::SHARKS)
			return 0;
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX() - 1] = MapPattern::TRAIL;
		if (charFrom == MapPattern::BORDER) {
			this->_lastBorderPosX = this->_manageMap._map.getPlayerX();
			this->_lastBorderPosY= this->_manageMap._map.getPlayerY();
		}
	} else if (charTo == MapPattern::BORDER && charFrom == MapPattern::TRAIL) {
		fillBox();
	}
	this->_manageMap._map.setPlayerX(this->_manageMap._map.getPlayerX() - 1);
	return 0;
}

int ar::Qix::ToRight(int charFrom)
{
	int charTo = GetCharTo(this->_manageMap._map.getPlayerX() + 1, this->_manageMap._map.getPlayerY());

	if (charTo == MapPattern::QIX)
		return 1;
	if (charTo == -1 || (charTo != MapPattern::WALKABLE && charTo != MapPattern::BORDER))
		return 0;
	if (charTo == MapPattern::WALKABLE) {
		charTo = GetCharTo(this->_manageMap._map.getPlayerX() + 2, this->_manageMap._map.getPlayerY());
		int charToSharks = GetCharTo(this->_manageMap._map.getPlayerX() + 1, this->_manageMap._map.getPlayerY() + 1);
		int charToSharksbis = GetCharTo(this->_manageMap._map.getPlayerX() + 1, this->_manageMap._map.getPlayerY() - 1);
		if (charTo == MapPattern::TRAIL || charTo == MapPattern::SHARKS ||
			charToSharks == MapPattern::TRAIL || charToSharks == MapPattern::SHARKS ||
			charToSharksbis == MapPattern::TRAIL || charToSharksbis == MapPattern::SHARKS)
			return 0;
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX() + 1] = MapPattern::TRAIL;
		if (charFrom == MapPattern::BORDER) {
			this->_lastBorderPosX = this->_manageMap._map.getPlayerX();
			this->_lastBorderPosY= this->_manageMap._map.getPlayerY();
		}
	} else if (charTo == MapPattern::BORDER && charFrom == MapPattern::TRAIL) {
		fillBox();
	}
	this->_manageMap._map.setPlayerX(this->_manageMap._map.getPlayerX() + 1);
	return 0;
}

int ar::Qix::movePlayer(void)
{
	static int (ar::Qix::*MoveTo[4])(int) = {&ar::Qix::ToLeft,
		&ar::Qix::ToRight, &ar::Qix::ToDown, &ar::Qix::ToUp};
	int charFrom = this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()];
	int ret = 0;

	if (!this->_isPlayerStopped)
		ret = (this->*MoveTo[this->_actualDir])(charFrom);
	if (ret) {
		this->_life -= 1;
		resetSpecificCharMap(MapPattern::TRAIL);
		this->_isPlayerStopped = true;
		this->_manageMap._map.setPlayerY(this->_lastBorderPosY);
		this->_manageMap._map.setPlayerX(this->_lastBorderPosX);
	}
	return ret;
}

int ar::Qix::QixToDown(void)
{
	std::size_t posTmp = this->_manageMap._posQixY;

	this->_manageMap._posQixY += 1;
	int ret = this->_manageMap.PlaceQixOntTheMap(this->_patternQix);

	if (ret == -1) {
		return 1;
	} else if (ret) {
		this->_manageMap._posQixY = posTmp;
		this->_manageMap.PlaceQixOntTheMap(this->_patternQix);
	}
	return 0;
}

int ar::Qix::QixToUp(void)
{
	std::size_t posTmp = this->_manageMap._posQixY;

	this->_manageMap._posQixY -= 1;
	int ret = this->_manageMap.PlaceQixOntTheMap(this->_patternQix);

	if (ret == -1) {
		return 1;
	} else if (ret) {
		this->_manageMap._posQixY = posTmp;
		this->_manageMap.PlaceQixOntTheMap(this->_patternQix);
	}
	return 0;
}

int ar::Qix::QixToLeft(void)
{
	std::size_t posTmp = this->_manageMap._posQixX;

	this->_manageMap._posQixX -= 1;
	int ret = this->_manageMap.PlaceQixOntTheMap(this->_patternQix);

	if (ret == -1) {
		return 1;
	} else if (ret) {
		this->_manageMap._posQixX = posTmp;
		this->_manageMap.PlaceQixOntTheMap(this->_patternQix);
	}
	return 0;
}

int ar::Qix::QixToRight(void)
{
	std::size_t posTmp = this->_manageMap._posQixX;

	this->_manageMap._posQixX += 1;
	int ret = this->_manageMap.PlaceQixOntTheMap(this->_patternQix);

	if (ret == -1) {
		return 1;
	} else if (ret) {
		this->_manageMap._posQixX = posTmp;
		this->_manageMap.PlaceQixOntTheMap(this->_patternQix);
	}
	return 0;
}

int ar::Qix::randomMoveQix(void)
{
	static int (ar::Qix::*MoveQixTo[4])(void) = {&ar::Qix::QixToLeft,
		&ar::Qix::QixToRight, &ar::Qix::QixToDown, &ar::Qix::QixToUp};
	int dir = rand() % 4;

	if ((this->*MoveQixTo[dir])() == 1) {
		this->_life -= 1;
		resetSpecificCharMap(MapPattern::TRAIL);
		this->_isPlayerStopped = true;
		this->_manageMap._map.setPlayerY(this->_lastBorderPosY);
		this->_manageMap._map.setPlayerX(this->_lastBorderPosX);
	}
	return (0);
}

void ar::Qix::SetDirFlameToGo()
{
	if (this->_lastBorderPosY + 1 < this->_manageMap._map.getHeight() && this->_manageMap._map[this->_lastBorderPosY + 1][this->_lastBorderPosX] == TRAIL) {
		_flame->setPosY(this->_lastBorderPosY + 1);
		_flame->setPosX(this->_lastBorderPosX);
		_flame->setDir(DirObj::DOWN);
	} else if (this->_lastBorderPosY - 1 >= 0 && this->_manageMap._map[this->_lastBorderPosY - 1][this->_lastBorderPosX] == TRAIL) {
		_flame->setPosY(this->_lastBorderPosY - 1);
		_flame->setPosX(this->_lastBorderPosX);
		_flame->setDir(DirObj::UP);
	} else if (this->_lastBorderPosX + 1 < this->_manageMap._map.getWidth() && this->_manageMap._map[this->_lastBorderPosY][this->_lastBorderPosX + 1] == TRAIL) {
		_flame->setPosY(this->_lastBorderPosY);
		_flame->setPosX(this->_lastBorderPosX + 1);
		_flame->setDir(DirObj::RIGHT);
	} else if (this->_lastBorderPosX - 1 >= 0 && this->_manageMap._map[this->_lastBorderPosY][this->_lastBorderPosX - 1] == TRAIL) {
		_flame->setPosY(this->_lastBorderPosY);
		_flame->setPosX(this->_lastBorderPosX - 1);
		_flame->setDir(DirObj::LEFT);
	}
}

void ar::Qix::KeyUpPressed(void)
{
	bool last = this->_isPlayerStopped;

	this->_isPlayerStopped = (this->_actualDir == DirObj::DOWN && this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::TRAIL);
	if (!last && this->_isPlayerStopped && !this->_flame) {
		_flame = new ManageSharks(this->_manageMap, true);
		SetDirFlameToGo();
		_flame->setLastChar(MapPattern::TRAIL);
		this->_manageMap._map[this->_manageMap._map.getHeight() - 1][this->_manageMap._map.getWidth() - 1] = MapPattern::BORDER;
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = MapPattern::SHARKS;
	}

	if (!this->_isPlayerStopped)
		this->_actualDir = DirObj::UP;
}

void ar::Qix::KeyDownPressed(void)
{
	bool last = this->_isPlayerStopped;

	this->_isPlayerStopped = (this->_actualDir == DirObj::UP && this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::TRAIL);
	if (!last && this->_isPlayerStopped && !this->_flame) {
		_flame = new ManageSharks(this->_manageMap, true);
		SetDirFlameToGo();
		_flame->setLastChar(MapPattern::TRAIL);
		this->_manageMap._map[this->_manageMap._map.getHeight() - 1][this->_manageMap._map.getWidth() - 1] = MapPattern::BORDER;
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = MapPattern::SHARKS;
	}

	if (!this->_isPlayerStopped)
		this->_actualDir = DirObj::DOWN;
}

void ar::Qix::KeyLeftPressed(void)
{
	bool last = this->_isPlayerStopped;

	this->_isPlayerStopped = (this->_actualDir == DirObj::RIGHT  && this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::TRAIL);
	if (!last && this->_isPlayerStopped && !this->_flame) {
		_flame = new ManageSharks(this->_manageMap, true);
		SetDirFlameToGo();
		_flame->setLastChar(MapPattern::TRAIL);
		this->_manageMap._map[this->_manageMap._map.getHeight() - 1][this->_manageMap._map.getWidth() - 1] = MapPattern::BORDER;
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = MapPattern::SHARKS;
	}

	if (!this->_isPlayerStopped)
		this->_actualDir = DirObj::LEFT;
}

void ar::Qix::KeyRightPressed(void)
{
	bool last = this->_isPlayerStopped;

	this->_isPlayerStopped = (this->_actualDir == DirObj::LEFT  && this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::TRAIL);
	if (!last && this->_isPlayerStopped && !this->_flame) {
		_flame = new ManageSharks(this->_manageMap, true);
		SetDirFlameToGo();
		_flame->setLastChar(MapPattern::TRAIL);
		this->_manageMap._map[this->_manageMap._map.getHeight() - 1][this->_manageMap._map.getWidth() - 1] = MapPattern::BORDER;
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = MapPattern::SHARKS;
	}

	if (!this->_isPlayerStopped)
		this->_actualDir = DirObj::RIGHT;
}

void ar::Qix::manageKey(const ar::Event &key)
{
	static void (ar::Qix::*keyPressed[4])(void) = {&ar::Qix::KeyUpPressed,
		&ar::Qix::KeyDownPressed, &ar::Qix::KeyLeftPressed,
		&ar::Qix::KeyRightPressed};

	if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::PLAYER)
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] = this->_behindPlayer;

	if (key == Event::AR_PAUSE)
		this->_isPaused = !this->_isPaused;
	else if (this->_isPaused)
		return;
	else if ((int)key < 4)
		(this->*keyPressed[key])();
}

int ar::Qix::GoThroughTheMap(int x, int y)
{
	if (x < 0 || y < 0 || this->_manageMap._map.getHeight() <= y || this->_manageMap._map.getWidth() <= x)
		return 0;
	if (this->_manageMap._map[y][x] != MapPattern::WALKABLE &&
		this->_manageMap._map[y][x] != MapPattern::QIX) {
		if (this->_manageMap._map[y][x] == MapPattern::OLDBORDER)
			this->_manageMap._map[y][x] = MapPattern::BORDER;
		return 0;
	}
	if (x < this->_manageMap._map.getWidth() && y < this->_manageMap._map.getHeight() && x > 0 && y > 0) {
		this->_manageMap._map[y][x] = MapPattern::FILLQIXTMP;

		GoThroughTheMap(x, y + 1);
		GoThroughTheMap(x, y - 1);

		GoThroughTheMap(x + 1, y);
		GoThroughTheMap(x - 1, y);

		GoThroughTheMap(x + 1, y + 1);
		GoThroughTheMap(x - 1, y - 1);

		GoThroughTheMap(x - 1, y + 1);
		GoThroughTheMap(x + 1, y - 1);
	}

	return 0;
}

void ar::Qix::fillBox(bool opt)
{
	for (int idx_y = 0;
		idx_y < this->_manageMap._map.getHeight(); ++idx_y) {
		for (int idx_x = 0;
			idx_x < this->_manageMap._map.getWidth(); ++idx_x) {
			if (this->_manageMap._map[idx_y][idx_x] == MapPattern::BORDER || (this->_manageMap._map[idx_y][idx_x] == MapPattern::TRAIL && !opt))
				this->_manageMap._map[idx_y][idx_x] = MapPattern::OLDBORDER;
		}
	}

	GoThroughTheMap((int)this->_manageMap._posQixX,
		(int)this->_manageMap._posQixY);

	for (int idx_y = 0;
		idx_y < this->_manageMap._map.getHeight(); ++idx_y) {
		for (int idx_x = 0;
			idx_x < this->_manageMap._map.getWidth(); ++idx_x) {
			if (this->_manageMap._map[idx_y][idx_x] == MapPattern::WALKABLE)
				this->_manageMap._map[idx_y][idx_x] = MapPattern::NOWALKABLE;
			else if (this->_manageMap._map[idx_y][idx_x] == MapPattern::FILLQIXTMP)
			this->_manageMap._map[idx_y][idx_x] = MapPattern::WALKABLE;
		}
	}
	this->_manageMap.PlaceQixOntTheMap(0);
}

void ar::Qix::updateMap(void) {
	int **mapTmp = new int *[this->_manageMap._map.getHeight() + 1];
	for (int i = 0; i < this->_manageMap._map.getHeight(); ++i) {
		mapTmp[i] = new int[this->_manageMap._map.getWidth() + 1];
		for (int j = 0; j < this->_manageMap._map.getWidth(); ++j) {
			mapTmp[i][j] = this->_manageMap._map[i][j];
			if (this->_manageMap._map[i][j] == MapPattern::SHARKS)
				this->_manageMap._map[i][j] = MapPattern::BORDER;
			if (this->_manageMap._map[i][j] != MapPattern::BORDER && this->_manageMap._map[i][j] != MapPattern::OLDBORDER)
				this->_manageMap._map[i][j] = MapPattern::WALKABLE;
		}
		mapTmp[i][this->_manageMap._map.getWidth()] = 0;
	}
	mapTmp[this->_manageMap._map.getHeight()] = nullptr;

	GoThroughTheMap((int)this->_manageMap._posQixX,
		(int)this->_manageMap._posQixY);
	for (int idx_y = 0;
		idx_y < this->_manageMap._map.getHeight(); ++idx_y) {
		for (int idx_x = 0;
			idx_x < this->_manageMap._map.getWidth(); ++idx_x) {
			if (this->_manageMap._map[idx_y][idx_x] == MapPattern::WALKABLE)
				this->_manageMap._map[idx_y][idx_x] = MapPattern::NOWALKABLE;
			else if (this->_manageMap._map[idx_y][idx_x] == MapPattern::FILLQIXTMP)
				this->_manageMap._map[idx_y][idx_x] = MapPattern::WALKABLE;
			if (mapTmp[idx_y][idx_x] == MapPattern::SHARKS || mapTmp[idx_y][idx_x] == MapPattern::TRAIL)
				this->_manageMap._map[idx_y][idx_x] = mapTmp[idx_y][idx_x];
		}
	}
	for (int i = 0; i < this->_manageMap._map.getHeight(); ++i) {
		delete[] mapTmp[i];
	}
	delete[] mapTmp;
}

void ar::Qix::resetSpecificCharMap(MapPattern car)
{
	for (int idx_y = 0;
		idx_y < this->_manageMap._map.getHeight(); ++idx_y) {
		for (int idx_x = 0;
			idx_x < this->_manageMap._map.getWidth(); ++idx_x) {
			if (this->_manageMap._map[idx_y][idx_x] == car)
				this->_manageMap._map[idx_y][idx_x] = MapPattern::WALKABLE;
		}
	}
}

const std::string ar::Qix::getGameName() const
{
	return "Qix";
}

const std::string ar::Qix::getSpritesPath() const
{
	return this->_spritePath;
}

const std::map<unsigned char, ar::spriteCoords> &ar::Qix::getSprites() const
{
	return this->_sprites;
}

std::size_t ar::Qix::getLife() const
{
	return this->_life;
}

int ar::Qix::getLastBorderPosX() const
{
	return this->_lastBorderPosX;
}

int ar::Qix::getLastBorderPosY() const
{
	return this->_lastBorderPosY;
}

int ar::Qix::refreshScore()
{
	return this->_data.score;
}

int ar::Qix::refreshTimer()
{
	int	newTime;

	if (_isPaused == true && _startPause == -1) {
		_startPause = clock();
	} else if (_isPaused == true) {
		if (clock() - _startPause > 1000000) {
			_startPause = clock();
			_timer++;
		}
	} else if (_startPause != -1) {
		_startPause = -1;
	}
	newTime = std::time(nullptr) - _timer;
	if (newTime >= _tmpTimer && _isPaused == false)
		_tmpTimer = newTime;
	return _tmpTimer;
}

extern "C" ar::Qix *createGame()
{
	return new ar::Qix;
}

extern "C" void destroyGame(ar::Qix *obj)
{
	delete obj;
}
