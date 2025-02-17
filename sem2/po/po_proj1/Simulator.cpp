#include "Simulator.h"

Simulator* Simulator::Init_World()
{
	int height = 0;
	int width = 0;

	std::cout << "\n\t---Initialising new world simulation---";
	std::cout << "\nEnter the height of the new world: ";
	std::cin >> height;
	std::cout << "\nEnter the width of the new world: ";
	std::cin >> width;

    while (height <= 0 || width <= 0) {
        std::cout << "\n\n\tPlease enter proper dimensions (ints bigger than 0)";
        std::cout << "\nEnter the height of the new world: ";
        std::cin >> height;
        std::cout << "\nEnter the width of the new world: ";
        std::cin >> width;
    }

	self = new Simulator(width, height);
    self->populate_world();

	return self;
}

Simulator* Simulator::MainMenu()
{
    int key_pressed = 0;

    while (key_pressed != KEY_Q)
    {
        std::cout << "\n\t*** Initialising new simulator ***";
        std::cout << "\n> Press N to create new world";
        std::cout << "\n> Press L to load saved world";
        std::cout << "\n> Press Q to exit simulator\n";
        key_pressed = getch();

        if (key_pressed == KEY_N) {
            std::cout << "\n\n";
            Init_World();
            break;
        }
        else if (key_pressed == KEY_L)
        {
            std::cout << "\n\n";
            self = new Simulator();
            self->world = load_world();
            if (self->world == nullptr) {
                delete self;
                self = nullptr;
                std::cout << "\n\tError loading savefile. Please try again or create a new world.";
            } 
            else
                break;
        }
        else
        {
            if (key_pressed != KEY_Q)
            std::cout << "\n\n\tUnknown input";
        }
    }

    return self;
}

Simulator::Simulator(int world_size_x, int world_size_y)
	: world(new World(world_size_x, world_size_y)), turn_number(0)
{}

Simulator::Simulator()
    : world(nullptr), turn_number(0)
{}

Simulator::~Simulator()
{
    delete world;
    delete self;
}

Simulator* Simulator::self = 0;

Simulator* Simulator::Instance() {
	if (self == 0) {
        MainMenu();
	}
	return self;
}


int Simulator::save_world(World* w)
{
    std::string fname("saves/");
    std::string name;
    std::cout << "\n\n\tEnter filename to save your world state to: ";
    std::cin >> name;
    fname += name;
    fname += ".dat";

    std::ofstream f(fname, std::ios::out | std::ios::binary);
    if (!f) {
        std::cout << "Error on file open\n";
        return 1;
    }

    std::list<MinOrganism> mino;
    for (Organism* o : w->get_organisms_list()) {
        if (o->get_symbol() != HUMAN_SYMBOL) {
            mino.push_back(o->minify());
        }
    }

    MinHuman minh;
    if (w->get_human() != nullptr) {
        minh = dynamic_cast<Human*>(w->get_human())->minify_human();
    }
    else {

        minh.x = -1;
        minh.y = -1;
        minh.symbol = 'E';
        minh.strength = -1;
        minh.skill_duration_left = -1;
        minh.skill_cooldown = -1;
    }

    int x = w->get_map().get_size_x();
    int y = w->get_map().get_size_y();
    //zapisaæ numer tury
    int turn = turn_number;

    f.write((char*)&x, sizeof(int));
    f.write((char*)&y, sizeof(int));
    f.write((char*)&turn, sizeof(int));

    f.write((char*)&minh, sizeof(MinHuman));



    for (MinOrganism min : mino) {
        f.write((char*)&min, sizeof(MinOrganism));
        //std::cout << min.x << ", " << min.y << "-" << min.strength << "=" << min.symbol << std::endl;
    }


    f.close();
    if (!f.good())
    {
        std::cout << "writing error\n";
        return 1;
    }

    std::cout << "\nWorld saved";
}

World* Simulator::load_world() {
    std::string fname("saves/");
    std::string name;
    std::cout << "\n\t> Enter filename of your saved world: ";
    std::cin >> name;
    fname += name;
    fname += ".dat";

    std::ifstream f(fname, std::ios::out | std::ios::binary);
    if (!f) {
        std::cout << "Error on file load\n";
        return nullptr;
    }

    int x = 0;
    int y = 0;
    int turn = 0;
    f.read((char*)&x, sizeof(int));
    f.read((char*)&y, sizeof(int));
    f.read((char*)&turn, sizeof(int));
    self->turn_number = turn;

    MinHuman minh;
    f.read((char*)&minh, sizeof(MinHuman));

    MinOrganism mino;
    World* w = new World(x, y);

    if (!(minh.x == -1 && minh.y == -1)) {
        w->set_human(w->add_organism(new Human(minh.x, minh.y, *w)));
        Human* h = dynamic_cast<Human*>(w->get_human());

        h->set_strength(minh.strength);
        h->set_id(-1 * minh.id);
        h->set_skill_cooldown(minh.skill_cooldown);
        h->set_skill_duration_left(minh.skill_duration_left);
        if (minh.skill_duration_left > 0)
            h->set_skill_active(true);
    }
    else {
        w->set_human(nullptr);
    }

    Organism* new_o = nullptr;
    while (f.read((char*)&mino, sizeof(MinOrganism)))
    {
        new_o = nullptr;


        if (mino.symbol == SHEEP_SYMBOL) {
            new_o = w->add_organism(new Sheep(mino.x, mino.y, *w));
        }
        else if (mino.symbol == WOLF_SYMBOL) {
            new_o = w->add_organism(new Wolf(mino.x, mino.y, *w));
        }
        else if (mino.symbol == ANTELOPE_SYMBOL) {
            new_o = w->add_organism(new Antelope(mino.x, mino.y, *w));
        }
        else if (mino.symbol == FOX_SYMBOL) {
            new_o = w->add_organism(new Fox(mino.x, mino.y, *w));
        }
        else if (mino.symbol == TURTLE_SYMBOL) {
            new_o = w->add_organism(new Turtle(mino.x, mino.y, *w));
        }

        else if (mino.symbol == GRASS_SYMBOL) {
            new_o = w->add_organism(new Grass(mino.x, mino.y, *w));
        }
        else if (mino.symbol == DANDELLION_SYMBOL) {
            new_o = w->add_organism(new Dandellion(mino.x, mino.y, *w));
        }
        else if (mino.symbol == GUARANA_SYMBOL) {
            new_o = w->add_organism(new Guarana(mino.x, mino.y, *w));
        }
        else if (mino.symbol == NIGHTSHADE_SYMBOL) {
            new_o = w->add_organism(new Nightshade(mino.x, mino.y, *w));
        }
        else if (mino.symbol == PINE_BORSCHT_SYMBOL) {
            new_o = w->add_organism(new Pine_Borscht(mino.x, mino.y, *w));
        }


        if (new_o != nullptr)
        {
           new_o->set_strength(mino.strength);
           new_o->set_id(-1 * minh.id);
        }
    }


    f.close();
    /*if (!f.good())
    {
        std::cout << "reading error\n";
        return nullptr;
    }*/

    return w;
}

void Simulator::populate_world()
{
    int x = this->world->get_map().get_size_x();
    int y = this->world->get_map().get_size_y();
    int o_density = (x * y) * 0.1 ;

    if (o_density < 0) return;

    int xi = rand() % x;
    int yi = rand() % y;
    int type = -1;


    this->world->set_human(this->world->add_organism(new Human(x / 2, y / 2, *world)));
    for (int i = 0; i < o_density; i++)
    {
        xi = rand() % x;
        yi = rand() % y;
        type = rand() % ORGANISM_TYPES;

        if (world->get_organism_at_location(XY(xi, yi)) == nullptr)
        {
            this->spawn_organism(xi, yi, type);
        }
        else
            --i;
    }
}

void Simulator::spawn_organism(int x, int y, int type)
{
    switch (type)
    {
        case(0):
            this->add_organism_to_world(new Sheep(x, y, *world));
            break;
        case(1):
            this->add_organism_to_world(new Wolf(x, y, *world));
            break;
        case(2):
            this->add_organism_to_world(new Fox(x, y, *world));
            break;
        case(3):
            this->add_organism_to_world(new Turtle(x, y, *world));
            break;
        case(4):
            this->add_organism_to_world(new Antelope(x, y, *world));
            break;

        case(5):
            this->add_organism_to_world(new Grass(x, y, *world));
            break;
        case(6):
            this->add_organism_to_world(new Dandellion(x, y, *world));
            break;
        case(7):
            this->add_organism_to_world(new Guarana(x, y, *world));
            break;
        case(8):
            this->add_organism_to_world(new Nightshade(x, y, *world));
            break;
        case(9):
            this->add_organism_to_world(new Pine_Borscht(x, y, *world));
            break;

    }
}

void Simulator::simulate_world()
{
    if (self->world == nullptr)
        return;


    int key_pressed = 0;
    int is_arrow_key = 0;

    this->world->draw_world();

    while (key_pressed != EXIT_KEY)
    {
        is_arrow_key = 0;
        key_pressed = getch();

        if ((key_pressed == 0 || key_pressed == 224) && this->world->get_human() != nullptr)
        {
            is_arrow_key = 1;
            key_pressed = getch();
            this->world->get_human()->control(key_pressed);
        }
        else if (key_pressed == HUMAN_SKILL_KEY && this->world->get_human() != nullptr)
        {
            this->world->get_human()->control(key_pressed);
        }
        else if (key_pressed == SAVE_WORLD_KEY)
        {
            save_world(this->world);
            //std::cout << "\n\n\t Not avaiable\n";
        }
        else
        { }

        this->world->make_turn();

        this->turn_number++;
        std::cout << "\n\n\t ### Turn nr " << this->turn_number << " ###\n\n";
        this->world->draw_world();
    }




}