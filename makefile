tileTest: tileTest.h tileTest.cpp
	g++ tileTest.cpp -o testing/tile -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/tile

playerTest: Player.h PlayerTest.cpp tileTest.h 
	g++ PlayerTest.cpp -o testing/player -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/player

plantInventoryTest: PlayerPlantInv.h PlayerTest.cpp tile.h Plant.h BerryPlant.h
	g++ PlayerTest.cpp -o testing/plantInventory -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/plantInventory

plantImage: Plant.h PlantTest.cpp tile.h
	g++ PlantTest.cpp -o testing/plantImage -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/plantImage

rootPlant: RootPlantTest.cpp RootPlant.h Plant.h tile.h 
	g++ RootPlantTest.cpp -o testing/rootplant -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/rootplant

berryPlant: BerryPlantTest.cpp BerryPlant.h Plant.h tile.h 
	g++ BerryPlantTest.cpp -o testing/berryPlantImage -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/berryPlantImage

carrot: CarrotTest.cpp Carrot.h RootPlant.h Plant.h tile.h 
	g++ CarrotTest.cpp -o testing/carrot -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/carrot

potato: PotatoTest.cpp Potato.h RootPlant.h Plant.h tile.h 
	g++ PotatoTest.cpp -o testing/potato -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/potato

blueberry: BlueberryTest.cpp Blueberry.h BerryPlant.h Plant.h tile.h 
	g++ BlueberryTest.cpp -o testing/blueberry -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/blueberry

strawberry: strawberryTest.cpp Strawberry.h BerryPlant.h Plant.h tile.h 
	g++ strawberryTest.cpp -o testing/strawberry -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/strawberry

plantAndPlayerTest: PlayerPlantInv.h PlayerTest.cpp tile.h Plant.h
	g++ PlayerTest.cpp -o testing/plantMove -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/plantMove

# textTest: TextboxTest.cpp TextBox.h tile.h Player.h
# 	g++ TextboxTest.cpp -o testing/text -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
# 	./testing/text

buymenuTest: BuyMenuTest.cpp Menu.h BuyMenu.h Player.h
	g++ BuyMenuTest.cpp -o testing/buymenu -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/buymenu

menuTest: MenuTest.cpp menu.h tile.h Player.h
	g++ MenuTest.cpp -o testing/menu -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/menu

# playerInteractionTest: PlayerInteractionTest.cpp PlayerInteraction.h tile.h Player.h Carrot.h
# 	clang++ PlayerInteractionTest.cpp -o playerInteraction -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
# 	./playerInteraction

inventoryTest: InventoryTest.cpp Inventory.h Player.h tile.h BuyMenu.h
	g++ InventoryTest.cpp -o testing/inventory -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/inventory

playerInteractionTest: PlayerInteractionTest.cpp PlayerInteraction.h tile.h Player.h Carrot.h
	clang++ PlayerInteractionTest.cpp -o testing/playerInteraction -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/playerInteraction

dayTest: DayTest.cpp Day.h tile.h Player.h
	clang++ DayTest.cpp -o testing/day -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/day

sellmenuTest: SellMenuTest.cpp Menu.h BuyMenu.h Player.h SellMenu.h
	g++ SellMenuTest.cpp -o testing/sellmenu -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/sellmenu

# has everything i.e. inventory, can plant plants, water plants, clock et.
everythingdayTest: dayEverythingTest.cpp Day.h BuyMenu.h menu.h Player.h Strawberry.h Blueberry.h Carrot.h Potato.h RootPlant.h BerryPlant.h Plant.h tile.h InventoryItems.h
	clang++ dayEverythingTest.cpp -o testing/everythingDay -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/everythingDay

inventoryImageTest: InventoryImageTest.cpp InventoryItems.h tile.h
	g++ InventoryImageTest.cpp -o testing/inven -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/inven

menuTextTest: mainMenuTextTest.cpp Day.h BuyMenu.h menu.h Player.h Strawberry.h Blueberry.h Carrot.h Potato.h RootPlant.h BerryPlant.h Plant.h tile.h InventoryItems.h
	clang++ mainMenuTextTest.cpp -o testing/menuText -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/menuText

killPlantsTest: mainKillPlantsTest.cpp Day.h BuyMenu.h menu.h Player.h Strawberry.h Blueberry.h Carrot.h Potato.h RootPlant.h BerryPlant.h Plant.h tile.h InventoryItems.h
	clang++ mainKillPlantsTest.cpp -o testing/killPlants -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/killPlants

harvestPlantsTest: harvestTest.cpp Day.h BuyMenu.h menu.h Player.h Strawberry.h Blueberry.h Carrot.h Potato.h RootPlant.h BerryPlant.h Plant.h tile.h InventoryItems.h
	clang++ harvestTest.cpp -o testing/harvestTest -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/harvestTest

walletTest: walletAndSaveTest.cpp Day.h BuyMenu.h menu.h Player.h Strawberry.h Blueberry.h Carrot.h Potato.h RootPlant.h BerryPlant.h Plant.h tile.h InventoryItems.h
	clang++ walletAndSaveTest.cpp -o testing/walletTest -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/walletTest

saveTest: SaveGameTest.cpp SaveGame.h Day.h BuyMenu.h menu.h Player.h Strawberry.h Blueberry.h Carrot.h Potato.h RootPlant.h BerryPlant.h Plant.h tile.h InventoryItems.h
	clang++ SaveGameTest.cpp -o testing/saveTest -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 ./lib
	./testing/saveTest


Play: Game.cpp Game.h Day.h BuyMenu.h menu.h Player.h Strawberry.h Blueberry.h Carrot.h Potato.h RootPlant.h BerryPlant.h Plant.h tile.h InventoryItems.h
	clang++ Game.cpp -o release/Game -I include -L lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath -std=c++11 -Wall -Werror ./lib
	./release/Game



clean: 
	rm testing/tile testing/player testing/plantInventory testing/plantImage testing/rootplant testing/berryPlantImage testing/carrot testing/potato testing/blueberry testing/strawberry testing/plantMove testing/buymenu testing/menu testing/inventory testing/day testing/sellmenutesting/everythingDay testing/inven testing/menuText testing/killPlants testing/harvestTest testing/walletTest testing/saveTest release/Game

all: # only works for files which don't rely on using underfined pure virtual functions
	make rootPlant
	make berryPlant
	make carrot
	make potato
	make strawberry
	make blueberry
	make buymenuTest
	make menuTest
	make inventoryTest
	make dayTest
	make sellmenuTest
	make everythingdayTest
	make inventoryImageTest
	make menuTextTest
	make killPlantsTest
	make harvestPlantsTest
	make walletTest
	make saveTest
	make Play
