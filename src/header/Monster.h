#include "Engine.h"
#include <avr/pgmspace.h>


class Monster {
public:
    // Default constructor
    Monster()
        : name("Monster"), attack(0), defense(0), speed(0), special(0), hp(0) {}

        // Constructor with parameters
    Monster(uint8_t id, const char* name, uint8_t attack, uint8_t defense, uint8_t speed, uint8_t special, uint8_t hp)
        : id(id), name(name), attack(attack), defense(defense), speed(speed), special(special), hp(hp) {}


    // Getter functions
    uint8_t getID() const { return id; }
    const char* getName() const { return name; }
    uint8_t getAttack() const { return attack; }
    uint8_t getDefense() const { return defense; }
    uint8_t getSpeed() const { return speed; }
    uint8_t getSpecial() const { return special; }
    uint8_t getHP() const { return hp; }

    // Function to simulate a monster taking damage
    void takeDamage(uint8_t damage) {
        hp -= damage;
        if (hp < 0) {
            hp = 0;
        }
    }
  void drawMonster(const Monster& monster);
private:
    uint8_t id;
    const char* name;
    uint8_t attack;
    uint8_t defense;
    uint8_t speed;
    uint8_t special;
    float hp;

    friend class MonsterFactory;
};

class MonsterFactory {
public:
        static Monster createRandomMonster() {
        uint8_t id = getRandomNumber(1, 26);
        const char* name = getMonsterName(id);
        uint8_t attack = getRandomNumber(10, 20);
        uint8_t defense = getRandomNumber(5, 15);
        uint8_t speed = getRandomNumber(15, 30);
        uint8_t special = getRandomNumber(10, 25);
        float hp = getRandomNumber(30, 50);

        return Monster(id, name, attack, defense, speed, special, hp);
    }

private:
    // Function to generate a random number between min and max (inclusive)
    static uint8_t getRandomNumber(int min, int max) {
        return random(26);
    }
    // Function to get the monster name based on the ID
  static const char* getMonsterName(int id) {
      switch (id) {/*
         // case 1: return "";
         // case 2: return "Lullufly";
         // case 3: return "";
         // case 4: return "";
         // case 5: return "";
          //case 6: return "Inkquill";
         // case 7: return "Duneears";
         // case 8: return "";
         // case 9: return "Whiskerward";
         // case 10: return "";
          //case 11: return "Hailtusk";
          //case 12: return "Optishield";
          case 13: return "Pincholith";
          case 14: return "Marrowbite";
          case 15: return "Batlisk";
          case 16: return "Cephelum";
         // case 17: return "";
         // case 18: return "";
         // case 19: return "";
         // case 20: return "";
          case 21: return "Raptaroo";
         // case 22: return "";
          case 23: return "Solarion";
          case 24: return "Herculex";
          case 25: return "Paleviper";
          case 26: return "Leviawing";
          // Add more cases for other monster IDs*/
          default: return "";
      }
  }
};