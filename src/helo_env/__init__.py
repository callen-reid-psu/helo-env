"""
Author(s): Callen Reid
Date Created: 08/30/2026
Description:
HeloEnv: a Gymnasium environment wrapping a C helicopter flight dynamics model.
"""

from gymnasium.envs.registration import register

from helo_env.envs.helo_env import HeloEnv

__version__ = "0.1.0"
__all__ = ["HeloEnv"]

register(
    id="HeloEnv-v0",
    entry_point="helo_env.envs.helo_env:HeloEnv",
    max_episode_steps=1000,
)
