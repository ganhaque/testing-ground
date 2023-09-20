# Classes

# TODO
- Maybe separate texture & stuffs into a Sprite2D class?
- Rework Transition Tile
  - Change gridSize to +1, +1. The grid has 1 row & 1 column invisible to player
- Game variable should be initialize via JSON parsing
- Make a string parser helper classs that separate stuffs by "-"
  - Inventory items should be in the format "d-item_name"
  - Room should be in the format "d-d"
- Maybe: character has an overlay over the tile they are facing

# Character

```plantuml
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml

class Character {
- id: string
- x: int
- y: int
- stats: Stats
- facing: Direction
- Texture2D texture
- Rectangle frameRects[4]
- currentFrame: int

+ Character(int startX, int startY)
+ move(newX: int, newY: int): void
}

Character -right-> Direction
enum Direction {
  UP
  RIGHT
  DOWN
  LEFT
}


Stats --* Character
class Stats {
  int level
  int maxHp
  int atkDmg
  int abilityPower
  int armor
}

Inventory --* Character
class Inventory {
  foods: vector<string>
  equipments: string[]
  general: string[]
  keyItems: string[]
  questCompleted: string[]
}

```

# Tiles

```plantuml
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml
class Tile {
- id: string
- interactable: bool;
- blockMovement: bool;
- x: int;
- y: int;

- draw(gridSize: int): void
- interact(): void
}

class TransitionTile {
- x: int;
- y: int;
- newRoomId: string
}


```

# Game

```plantuml
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml

class Game {
- screenWidth: const int = 1600
- screenHeight: const int = 1000
- gridSize: const int = 50
- moveSpeed: double = 0.1
- lastMoveTime: double
- grid: int[][]
- currentRoomId: string
- saveInterval: int
- isLoading: bool
- completed: string[]
- interactableTiles: vector<Tile*>
- transitionTiles: vector<TransitionTile*>

- handleUserInput(): void
' - handleKeyboardInput(): void
' - handleMouseInput(): void
- isValidMove(newX: int, newY: int): bool
- loadRoom(roomId: string): void
+ run(): void
}

```

# Helpers
```plantuml
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml

class StringParser {
  + static std::tuple<int, std::string> ParseString(const std::string& input);
}

```

# Example Save Data (save_data.json)

```plantuml
@startjson
{
   "currentRoomId":"05-05",
   "completed": ["tutorial", "boss_1", "chest_1"],
   "inventory": ["1-hp_pot", "1-rock"],
   "playerX": 6,
   "playerY": 6
}
@endjson
```
# Example room (05-05.json)
```plantuml
@startjson
{
  "roomId":"05-05",
  "specialTiles": [
    {
      "id": "chest-1",
      "x": "3",
      "y": "3"
    },
    {
      "id": "npc-1",
      "x": "4",
      "y": "3"
    }
  ]
}
@endjson
```


<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

# Functions

## Game

```plantuml
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml

package parseRoomJSON(roomId: string) {
start
: find & load {roomId}.json;
: currentRoomId = room["roomId].asString();

repeat
  :k++;
repeat while (true)

end
}

package loadRoom(roomId: string) {
start
: parseRoomJSON();
: find {roomId}-bg.png for room;
: find {roomId}-fg.png for room;
end
}

package run() {
start
: clearBackground(RAYWHITE);
: render room background;
: render character & objects;
: render room foreground;
end
}
```





---



```plantuml
@startuml
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml

start
:Input;
note right: "Input data"
:letters_only();
note right: "Extract letters"
:encode();
note right: "Encode as digits"
:coalesce();
note right: "Coalesce adjacent digits"
:discard_zeros();
note right: "Discard zeros"
:truncate_or_pad();
note right: "Pad or truncate to length 4"
stop

@enduml
```

# Mindmap
```plantuml
@startuml
@startmindmap
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml
+ root
**:right_1.1
right_1.2;
++ right_2

left side

-- left_1
-- left_2
**:left_3.1
left_3.2;
@endmindmap
@enduml
```

# State

```plantuml
@startuml
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml

state choice1 <<choice>>
state fork1   <<fork>>
state join2   <<join>>
state end3    <<end>>

[*]     --> choice1 : from start\nto choice
choice1 --> fork1   : from choice\nto fork
choice1 --> join2   : from choice\nto join
choice1 --> end3    : from choice\nto end

fork1   ---> State1 : from fork\nto state
fork1   --> State2  : from fork\nto state

State2  --> join2   : from state\nto join
State1  --> [*]     : from state\nto end

join2   --> [*]     : from join\nto end
@enduml

@enduml
```

```plantuml
@startuml
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml


package "customer domain" {
class Contact {
+ email
+ phone
}

class Address {
+ address1
+ address2
+ city
+ region
+ country
+ postalCode
+ organization
}

note right of Address 
There are two types of 
addresses: billing and shipping
end note

class Customer {
}

Customer *-- Contact
Customer *-- ShippingAddress
Customer *-- BillingAddress
Customer *--{ SalesOrder

class ShippingAddress <<Address>>
class BillingAddress <<Address>>
class SalesOrder {
+ itemDescription
+ itemPrice
+ shippingCost
+ trackingNumber
+ shipDate
}
}
@enduml
```

# Object
```plantuml
@startuml
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml

object user1
user1 : name = "Dummy"
user1 : id = 123

object user2 {
name = "Dummy"
id = 123
}

object o1
object o2
diamond dia
object o3

o1  --> dia
o2  --> dia
dia --> o3
@enduml
```

# Deployment
```plantuml
@startuml
!include https://raw.githubusercontent.com/ganhaque/plantuml-theme/main/theme.yuml

actor actor
actor/ "actor/"
agent agent
artifact artifact
boundary boundary
card card
circle circle
cloud cloud
collections collections
component component
control control
database database
entity entity
file file
folder folder
frame frame
hexagon hexagon
interface interface
label label
node node
package package
person person
queue queue
rectangle rectangle
stack stack
storage storage
usecase usecase
usecase/ "usecase/"

@enduml
```
