-- A skeleton of a program for an assignment in programming languages
-- The students should rename the tasks of producers, consumers, and the buffer
-- Then, they should change them so that they would fit their assignments
-- They should also complete the code with constructions that lack there
with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO;
with Ada.Numerics.Discrete_Random;
with Ada.Strings.Bounded; use Ada.Strings;

procedure Simulation is
   Number_Of_Components : constant Integer := 5;
   Number_Of_Vessels    : constant Integer := 3;
   Number_Of_Fleets     : constant Integer := 2;

   subtype Component_Type is Integer range 1 .. Number_Of_Components;
   subtype Vessel_Type is Integer range 1 .. Number_Of_Vessels;
   subtype Fleet_Type is Integer range 1 .. Number_Of_Fleets;

   package Max_20_String is new Ada.Strings.Bounded.Generic_Bounded_Length
     (20);
   use Max_20_String;

   fleet_cap : exception;
   cap_exceeded : exception;

   Component_Names : constant array (Component_Type) of Bounded_String :=
     (To_Bounded_String ("Engine"), To_Bounded_String ("Power generator"),
      To_Bounded_String ("Hull"), To_Bounded_String ("Computer"),
      To_Bounded_String ("Armaments"));

   Vessel_Names : constant array (Vessel_Type) of Bounded_String :=
     (To_Bounded_String ("Yacht"), To_Bounded_String ("Cruiser"),
      To_Bounded_String ("Freighter"));

   package Random_Vessel is new Ada.Numerics.Discrete_Random (Vessel_Type);
   type My_Str is new String (1 .. 256);

   -- Producer produces determined product
   task type Component_Producer is
      -- Give the Producer an identity, i.e. the product type
      entry Start_Production
        (Component : in Component_Type; Production_Time : in Integer);
   end Component_Producer;

   -- Consumer gets an arbitrary assembly of several products from the buffer
   task type Fleet is
      -- Give the Consumer an identity
      entry Start
        (New_Fleet_Number            : in Fleet_Type;
         New_Vessel_Integration_Time : in Integer);
   end Fleet;

   -- In the Buffer, products are assemblied into an assembly
   task type Shipyard is
      -- Accept a product to the storage provided there is a room for it
      entry Take_Component
        (Component         : in     Component_Type; Component_ID : in Integer);
      -- Deliver an assembly provided there are enough products for it
      entry Deliver_Ready_Vessel
        (Vessel : in Vessel_Type; Vessel_ID : out Integer);
      entry CheckSpace(Production_Halted: out Boolean; Component: in Component_Type);
   end Shipyard;

   Comoponent_Producers : array
     (1 .. Number_Of_Components) of Component_Producer;
   Fleets        : array (1 .. Number_Of_Fleets) of Fleet;
   Main_Shipyard : Shipyard;

   task body Component_Producer is
      subtype Production_Time_Range is Integer range 10 .. 12;
      package Random_Production_Time is new Ada.Numerics.Discrete_Random
        (Production_Time_Range);
      Production_Time_Generator : Random_Production_Time
        .Generator;   --  generator liczb losowych
      Component_Type_Number : Component_Type;
      Current_Component_ID  : Integer;
      Production            : Integer;   --???
      Production_Halted     : Boolean := False;

   begin
      accept Start_Production
        (Component : in Component_Type; Production_Time : in Integer)
      do
         Random_Production_Time.Reset
           (Production_Time_Generator);    --  start random number generator
         Current_Component_ID  := 1;
         Component_Type_Number := Component;
         Production            := Production_Time;
      end Start_Production;

      Put_Line
        ("Started production of " &
         To_String (Component_Names (Component_Type_Number)));
      loop
         Put_Line("Checking and reserving space for " &
               To_String (Component_Names (Component_Type_Number)));
          Main_Shipyard.CheckSpace(Production_Halted, Component_Type_Number);
         delay Duration
              (Random_Production_Time.Random
                 (Production_Time_Generator)); --  symuluj produkcj\u00c4\u0099

         if Production_Halted then
            Put_Line
              ("Canceled production of component " &
               To_String (Component_Names (Component_Type_Number)));
         else
            Put_Line
              ("Produced component " &
               To_String (Component_Names (Component_Type_Number)) &
                 " number " & Integer'Image (Current_Component_ID));
                         Main_Shipyard.Take_Component
              (Component_Type_Number, Current_Component_ID);
            Current_Component_ID := Current_Component_ID + 1;
         end if;
      end loop;
   end Component_Producer;

   task body Fleet is
      subtype Vessel_Number is Integer range 0 .. 3;
      Number_Of_Vessels: Vessel_Number :=0;
      subtype Integration_Time_Range is Integer range 10 .. 12;
      package Random_Integration_Time is new Ada.Numerics.Discrete_Random
        (Integration_Time_Range);
      Integration_Time_Generator : Random_Integration_Time
        .Generator;  --  random number generator (time)
      Vessel_Type_Generator : Random_Vessel.Generator;    --  also (assemblies)
      Fleet_Number          : Fleet_Type;
      Requested_Vessel_ID   : Integer;
      Integration           : Integer;
      Requested_Vessel      : Integer;
      Fleet_Names : constant array (1 .. Number_Of_Fleets) of Bounded_String :=
        (To_Bounded_String ("Fleet1"), To_Bounded_String ("Fleet2"));
   begin
      accept Start
        (New_Fleet_Number            : in Fleet_Type;
         New_Vessel_Integration_Time : in Integer)
      do
         Random_Integration_Time.Reset
           (Integration_Time_Generator);   --  ustaw generator
         Random_Vessel.Reset (Vessel_Type_Generator);     --  też
         Fleet_Number := New_Fleet_Number;
         Integration  := New_Vessel_Integration_Time;
      end Start;

      Put_Line
        ("Started assembly of fleet " &
         To_String (Fleet_Names (Fleet_Number)));
      loop
         Requested_Vessel := Random_Vessel.Random (Vessel_Type_Generator);

         select
            -- take an assembly for consumption
            Main_Shipyard.Deliver_Ready_Vessel
              (Requested_Vessel, Requested_Vessel_ID);
            if Requested_Vessel_ID /= 0 then

               Put_Line
                 (To_String (Fleet_Names (Fleet_Number)) &
                    ": integrated vessel " &
                    To_String (Vessel_Names (Requested_Vessel)) & ". Number in the fleet: " &
                    Integer'Image (Number_Of_Vessels));
               if Number_Of_Vessels >= 3 then
                  raise fleet_cap;
               else
                  Number_Of_Vessels := Number_Of_Vessels +1;
               end if;
            end if;
            delay Duration
              (Random_Integration_Time.Random
                 (Integration_Time_Generator)); --  simulate consumption
         else
            Put_Line ("$$$Fleet wouldnt wait");
            delay Duration (8);
         end select;

         end loop;
      exception
         when fleet_cap =>
            Put_Line("Maximum fleet capacityh reached. Stopping vessel aqusition for " & To_String (Fleet_Names (Fleet_Number)));


   end Fleet;

   task body Shipyard is
      Component_Capacity : constant Integer := 30;
      type Storage_type is array (Component_Type) of Integer;
      Component_Storage : Storage_type := (0, 0, 0, 0, 0);
      Virtual_Components : Storage_type := (0, 0, 0, 0, 0);
      Vessel_Components : array (Vessel_Type, Component_Type) of Integer :=
        ((2, 1, 2, 1, 2), (2, 2, 0, 1, 0), (1, 1, 2, 0, 1));
      Max_Component_Content : array (Component_Type) of Integer;
      Assembled_Vessels     : array (Vessel_Type) of Integer := (1, 1, 1);
      Components_In_Storage : Integer                        := 0;
      Virtual_Component_Number:Integer :=0;
      Space_exceeded : Boolean := True;

      procedure Setup_Variables is
      begin
         for C in Component_Type loop
            Max_Component_Content (C) := 0;
            for V in Vessel_Type loop
               if Vessel_Components (V, C) > Max_Component_Content (C) then
                  Max_Component_Content (C) := Vessel_Components (V, C);
               end if;
            end loop;
         end loop;
      end Setup_Variables;

      function Can_Accept_Component (Component : Component_Type) return Boolean
      is
         Free_Storage_Room : Integer;         --  free room in the storage
         -- how many products are for production of arbitrary assembly
         Lacking_Min_Components : array (Component_Type) of Integer;
         -- how much room is needed in storage to produce arbitrary assembly
         Lacking_Storage_Room : Integer;
         MP                   : Boolean;                   --  can accept
      begin
         if Components_In_Storage >= Component_Capacity then
            return False;
         end if;

         -- There is free room in the storage
         Free_Storage_Room := Component_Capacity - Components_In_Storage;
         MP                := True;
         for C in Component_Type loop
            if Component_Storage (C) < Max_Component_Content (C) then
               MP := False;
            end if;
         end loop;
         if MP then
            return True;                --  storage has products for arbitrary
            --  assembly
         end if;
         if Integer'Max
             (0,
              Max_Component_Content (Component) -
              Component_Storage (Component)) >
           0
         then
            -- exactly this product lacks
            return True;
         end if;
         Lacking_Storage_Room :=
           1;                     --  insert current product
         for C in Component_Type loop
            Lacking_Min_Components (C) :=
              Integer'Max
                (0, Max_Component_Content (C) - Component_Storage (C));
            Lacking_Storage_Room :=
              Lacking_Storage_Room + Lacking_Min_Components (C);
         end loop;
         if Free_Storage_Room >= Lacking_Storage_Room then
            -- there is enough room in storage for arbitrary assembly
            return True;
         else
            -- no room for this product
            return False;
         end if;
      end Can_Accept_Component;

      function Can_Deliver_Vessel (Vessel : Vessel_Type) return Boolean is
      begin
         for C in Component_Type loop
            if (Component_Storage (C)-Virtual_Components(C)) < Vessel_Components (Vessel, C) then
               return False;
            end if;
         end loop;
         return True;
      end Can_Deliver_Vessel;

      procedure Show_Storage is
      begin
         Put ("Storage [");
         for C in Component_Type loop
            if C = 1 then
               Put (Integer'Image (Component_Storage (C)-Virtual_Components(C)));
            else
               Put (", " & Integer'Image (Component_Storage (C)-Virtual_Components(C)));
            end if;
         end loop;
         Put_Line ("]");
      end Show_Storage;

   begin
      Put_Line ("Buffer started");
      Setup_Variables;
      loop
         select
            accept Take_Component
              (Component         : in Component_Type; Component_ID : in Integer)

            do
               --if Can_Accept_Component (Component) then
                  Put_Line
                    ("Accepting component " &
                       To_String (Component_Names (Component)) & " number " &
                       Integer'Image (Component_ID));
                  Virtual_Components(Component) := Virtual_Components(Component) - 1;
               Virtual_Component_Number:=Virtual_Component_Number-1;



               Components_In_Storage := Components_In_Storage-1;
               Component_Storage(Component) := Component_Storage(Component)-1;



               if Can_Accept_Component(Component) then
                  Space_exceeded := False;

               end if;

               if not Space_exceeded then
                    Components_In_Storage := Components_In_Storage+1;
               Component_Storage(Component) := Component_Storage(Component)+1;
               else

                  Show_Storage;
                  raise cap_exceeded;
               end if;

              -- else
               --   Put_Line
               --     ("Rejected component " &
               --        To_String (Component_Names (Component)) & " number " &
               --        Integer'Image (Component_ID));
              -- end if;
               Show_Storage;
            end Take_Component;

         or

            accept Deliver_Ready_Vessel
           (Vessel : in Vessel_Type; Vessel_ID : out Integer)
            do
               if Can_Deliver_Vessel (Vessel) then
                  --raise test_exc;
                  Put_Line
                    ("Delivered vessel " & To_String (Vessel_Names (Vessel)) &
                       " number " & Integer'Image (Assembled_Vessels (Vessel)));
                  for C in Component_Type loop
                     Component_Storage (C) :=
                       Component_Storage (C) - Vessel_Components (Vessel, C);
                     Components_In_Storage :=
                       Components_In_Storage - Vessel_Components (Vessel, C);
                  end loop;
                  Vessel_ID                  := Assembled_Vessels (Vessel);
                  Assembled_Vessels (Vessel) := Assembled_Vessels (Vessel) + 1;

            else
               --raise test_exc;
                  Put_Line
                    ("Lacking products for assembly " &
                       To_String (Vessel_Names (Vessel)));

                  Vessel_ID := 0;
               end if;
            Show_Storage;
         end Deliver_Ready_Vessel;

         or
         accept CheckSpace (Production_Halted : out Boolean; Component: in Component_Type) do

               if Can_Accept_Component(Component) then
                    Component_Storage (Component) :=
                    Component_Storage (Component) + 1;
                  Components_In_Storage := Components_In_Storage + 1;
                  Virtual_Component_Number := Virtual_Component_Number+1;
                  Virtual_Components(Component) := Virtual_Components(Component) + 1;
                  Production_Halted := False;
               else
                  Production_Halted := True;
                 -- raise test_exc;
               end if;

         end CheckSpace;

         end select;

        end loop;



   exception
      --when test_exc =>
        -- Put_Line("Rasing again");
        -- raise;

      when cap_exceeded =>
            Put_Line("Lacking space! Reservation error!");

   end Shipyard;




begin
   for C in 1 .. Number_Of_Components loop
      Comoponent_Producers (C).Start_Production (C, 10);
   end loop;
   for F in 1 .. Number_Of_Fleets loop
      Fleets (F).Start (F, 12);
   end loop;
end Simulation;
