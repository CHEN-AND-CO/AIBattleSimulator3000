units = {
   "milice",
   "townCenter"
}

milice = {
   PositionComponent = {
      position = {
	 x = 10,
	 y = 10
      },
   },

   SpeedComponent = {
      speed = 10
   },

   HealthComponent = {
      health = 100
   },

   AttackComponent = {
      attackType = "melee",
      dommageType = "shock",
      amount = 2;
   },

   ArmorComponent = {
      pierce = 1,
      shock = 5,
      magic = 0
   }
}

townCenter = {
   PositionComponent = {
      position = {
	 x = 50,
	 y = 50
      },
   },

   HealthComponent = {
      health = 2000
   },

   AttackComponent = {
      attackType = "distance",
      dommageType = "pierce",
      amount = 8;
   },

   ArmorComponent = {
      pierce = 10,
      shock = 10,
      magic = 5
   }
}
