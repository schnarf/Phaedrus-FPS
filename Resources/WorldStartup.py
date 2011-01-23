from phaedrus import *

class PlayerEntity(PlayerEntityBase):
        def __init__(self, id):
                PlayerEntityBase.__init__(self, id)
                self._total_ms= 0
                self.look_vector= Vector(0, 0, -1)
                self.walk_speed= 0.05
                self.run_speed= 0.1
                self.default_eye_offset= Vector(0, 0, 0)
                self.crouch_eye_offset= Vector(0, -1, 0)
        def think(self, frame_ms):
                # Update our timer
                self._total_ms+= frame_ms
                while( self._total_ms > 1000 ):
                        print( '1 second elapsed!' )
                        self._total_ms-= 1000

                # Set our eye offset based on whether we are crouched
                if( g_input.is_key_down(InputKeys.INPUT_CTRL) ):
                        self.eye_offset= self.crouch_eye_offset
                else:
                        self.eye_offset= self.default_eye_offset
                        
                # Update our running/walking state
                if( g_input.is_key_down(InputKeys.INPUT_SHIFT) ):
                        cur_speed= self.run_speed
                else:
                        cur_speed= self.walk_speed
                if( g_input.is_key_down(InputKeys.INPUT_UP) ):
                        self.physics.velocity= Vector(0, 0, -cur_speed)
                elif( g_input.is_key_down(InputKeys.INPUT_DOWN) ):
                        self.physics.velocity= Vector(0, 0, cur_speed)
                else:
                        self.physics.velocity= Vector(0, 0, 0)

def WorldStartup():
	print( "World started up!" )
	localplayer= g_world.get_local_player_entity()
	print( "localplayer has id {0}".format(localplayer.get_id()) )
