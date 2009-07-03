function WorldStartup()
Print( "World started up!" );
localplayer= World:GetLocalPlayerEntity();
localplayer.LookVector= Vector(0.0, 0.0, -1.0);
localplayer.Velocity= Vector(0.0, 0.0, -0.001);
return 1;
end
