﻿using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace DrawableTrees
{
	/// <summary>
	/// This is the main type for your game.
	/// </summary>
	public class Game1 : Game
	{
		GraphicsDeviceManager graphics;
		SpriteBatch spriteBatch;

		// The three trees
		Tree treeRed;
		Tree treeGreen;
		Tree treeBlue;

		//random
		Random rng;
		public Game1()
		{
			graphics = new GraphicsDeviceManager(this);
			Content.RootDirectory = "Content";
		}

		/// <summary>
		/// Allows the game to perform any initialization it needs to before starting to run.
		/// This is where it can query for any required services and load any non-graphic
		/// related content.  Calling base.Initialize will enumerate through any components
		/// and initialize them as well.
		/// </summary>
		protected override void Initialize()
		{
			rng = new Random();

			base.Initialize();
		}

		/// <summary>
		/// LoadContent will be called once per game and is the place to load
		/// all of your content.
		/// </summary>
		protected override void LoadContent()
		{
			// Create a new SpriteBatch, which can be used to draw textures.
			spriteBatch = new SpriteBatch(GraphicsDevice);

			// Create the three trees
			treeRed = new Tree(Color.Red);
			treeGreen = new Tree(Color.Green);
			treeBlue = new Tree(Color.DodgerBlue);

			// TODO: Add logic to insert data into the red tree
			for (long i = 0; i < 1000; i++)
            {
				treeRed.Insert(rng.Next(2000));
			}

			// TODO: Add logic to insert data into the green tree
			for (long i = 0; i < 1000; i++)
			{
				treeGreen.Insert(500);
			}

			// TODO: Add logic to insert data into the blue tree
			for (long i = 0; i < 100; i++)
            {
				treeBlue.Insert(rng.Next(20));
            }

		}

		/// <summary>
		/// Allows the game to run logic such as updating the world,
		/// checking for collisions, gathering input, and playing audio.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Update(GameTime gameTime)
		{
			if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
				Exit();

			// TODO: If you want to play:
			//	After you have the rest of the assignment working:
			//  What happens if you insert a new piece of 
			//  data into the trees each frame?

			base.Update(gameTime);
		}

		/// <summary>
		/// This is called when the game should draw itself.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Draw(GameTime gameTime)
		{
			GraphicsDevice.Clear(Color.Black);

			// Draw the trees
			treeRed.Draw(new Vector2(150, 400), GraphicsDevice);
			treeGreen.Draw(new Vector2(300, 300), GraphicsDevice);
			treeBlue.Draw(new Vector2(600, 400), GraphicsDevice);

			base.Draw(gameTime);
		}
	}
}
