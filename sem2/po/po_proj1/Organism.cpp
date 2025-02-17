//
// Created by M Sz on 05/04/2023.
//
#include "Organism.h"

int Organism::organisms_counter = 0;

void Organism::draw()
{
    draw_symbol_at_xy(this->symbol, this->map_location);
}

int Organism::get_strength() const
{
    return this->strength;
}

int Organism::get_initiative() const
{
    return this->initiative;
}

XY Organism::get_location()
{
    return this->map_location;
}

int Organism::get_id() const
{
    return this->id;
}

int Organism::get_x() const
{
    return this->map_location.x;
}

int Organism::get_y() const
{
    return this->map_location.y;
}

char Organism::get_symbol() const
{
    return this->symbol;
}

World& Organism::get_world()
{
    return this->world;
}

int Organism::get_marker() const
{
    return this->marker;
}

void Organism::set_marker(int new_marker)
{
    this->marker = new_marker;
}


void Organism::set_strength(const int new_strength)
{
    this->strength = new_strength;
}

void Organism::set_initiative(const int new_initiative)
{
    this->initiative = new_initiative;
}

void Organism::set_location(const XY new_location)
{
    this->map_location = new_location;
}

void Organism::set_x(const int new_x)
{
    this->map_location.x = new_x;
}

void Organism::set_y(const int new_y)
{
    this->map_location.y = new_y;
}

void Organism::set_symbol(char new_symbol)
{
    this->symbol = new_symbol;
}

void Organism::set_world(World& new_world)
{
    this->world = new_world;
}



Organism::Organism(int new_strength, int new_initiative, XY new_map_location, char new_symbol, World& new_world)
    : strength(new_strength), initiative(new_initiative), map_location(new_map_location), world(new_world),
    id(organisms_counter + 1), symbol(new_symbol), marker(NULL_MARKER)
{
    organisms_counter++;

    //this->log("spawns");
}

Organism::Organism(int new_strength, int new_initiative, int new_x, int new_y, char new_symbol, World& new_world)
    : strength(new_strength), initiative(new_initiative), world(new_world), map_location(XY(new_x, new_y)),
    id(organisms_counter + 1), symbol(new_symbol), marker(NULL_MARKER)
{
    organisms_counter++;

    //this->log("spawns");
}


Organism::~Organism()
{
    //informacja
    std::cout << "destruktor organizmu\n";


    //od³¹czenie z listy
    //this->world.org.remove(this);

    //dealokacja samego obiektu

}

void Organism::kill_self() {
    //oznacza organizm jako nie¿ywy - do usuniêcia z listy organizmów
    this->set_marker(DEAD_MARKER);

    //log œmieræ orgainzmu
    this->log("Dies");

    //zdjêcie z mapy
    if (this->world.map.get_object(this->map_location) == this)
        this->world.map.lift_object_from_location(this->map_location);

    //delete this;


    //this->log("Dies");

    //if (this->world.map.get_object(this->map_location) == this)
    //    this->world.map.lift_object_from_location(this->map_location);
    //czyœci pole dotychczas zajmowane przez this tylko jeœli this dalej tam stoi


    //remove self wywo³uje destruktor Organizmu
}

void Organism::update_location(XY new_location) {

    std::string s("moves to (");
    s += std::to_string(new_location.x);
    s += ", ";
    s += std::to_string(new_location.y);
    s += ")";
    this->log(s);

    this->world.map.move_object(new_location, this);
    this->set_location(new_location);
}

void Organism::log(std::string info) {
    std::cout << "\t" << this->login() << "(" << this->get_x() << ", " << this->get_y() << ") " << info << "\n";
}

std::string Organism::login() {
    return std::string("Organizm");
}

bool Organism::is_plant() {
    if (this->initiative == 0) return true;
    return false;
}

bool Organism::is_plant(Organism* target) {
    if (target->get_initiative() == 0) return true;
    return false;
}

void Organism::control(int command)
{}

MinOrganism Organism::minify() {
    MinOrganism min;
    min.x = this->get_x();
    min.y = this->get_y();
    min.strength = this->get_strength();
    min.symbol = this->get_symbol();

    return min;
}