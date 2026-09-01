"""Core Gymnasium environment definition for the helicopter model.

This wraps the C model (via helo_env.native.bindings) in a gymnasium.Env
interface. Fill in observation/action space shapes and the physics call
once the C model's function signatures are known.
"""
from __future__ import annotations

from typing import Any, Optional

import gymnasium as gym
import numpy as np
from gymnasium import spaces

from helo_env.native import bindings


class HeloEnv(gym.Env):
    """Gymnasium environment for the C-based helicopter flight dynamics model."""

    metadata = {"render_modes": [], "render_fps": 30}

    def __init__(self,render_mode: Optional[str] = None,) -> None:
        super().__init__()
        self.render_mode = render_mode

        # TODO: replace placeholder dims once the C model's state/control
        # vector sizes are known.
        obs_dim = 9  
        act_dim = 4

        self.observation_space = spaces.Box(
            low=-np.inf, high=np.inf, shape=(obs_dim,), dtype=np.float32
        )
        self.action_space = spaces.Box(
            low=-1.0, high=1.0, shape=(act_dim,), dtype=np.float32
        )

        self._sim = bindings.HeloModel()

    def _get_obs(self)->dict[str,Any]:
            """Convert internal state to observation format.
    
            Returns:
                dict: Observation with agent and target positions
            """
            return {} # Ex: {"agent_position":self._agent_position}


    def _get_info(self)->dict[str,Any]:
            """Compute auxiliary information for debugging.
    
            Returns:
                dict: Info with distance between agent and target
            """
            return {} # Ex: {"Delta":self._x2 - self._x1}

    def reset(self, *, seed: Optional[int] = None, options: Optional[dict] = None
              )->tuple[dict[str,Any],...]:
        """_summary_

        Parameters
        ----------
        seed : Optional[int], optional
            Random seed for reproducibility, by default None
        options : Optional[dict], optional
            Additional configuration (currently unused), by default None

        Returns
        -------
        tuple[dict[str,Any],...]
            The observations and info from the reset
        """
        super().reset(seed=seed)

        state = self._sim.reset()
        obs = self._get_obs()
        info = self._get_info()
        return obs, info

    def step(self, action: np.ndarray):
        raise NotImplementedError("Step not yet implemented for HeloEnv.")

    def render(self):
        raise NotImplementedError("Rendering not yet implemented for HeloEnv.")

    def close(self):
        self._sim.close()
