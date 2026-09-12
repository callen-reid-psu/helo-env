"""Basic sanity tests for the HeloEnv gymnasium environment.

These will fail until native/bindings.py is wired up to the real C model —
that's expected until the model arrives and is integrated. Kept here as a
starting scaffold / TODO marker.
"""
import gymnasium as gym
import pytest

import numpy as np

from helo_env.native import bindings

class TestBindings:
    @pytest.fixture(autouse=True)
    def set_flight_conditions(self):
        self.fc = {'vx_trim':50.0*1.688,
                    'vy_trim':0.0,
                    'vz_trim':0.0,
                    'psid_trim':0.0,
                    'psi_trim':0.0,
                    'z_trim':100.0,
                    'x_trim':0.0,
                    'y_trim':0.0}

    def test_reset(self):
        """Tests the reset function of the HeloModel class in bindings.py. This test checks that the
        reset funciton correctly calls the InitH60 function in the C model."""
        helo = bindings.HeloModel()
        helo.reset(self.fc)
        

    def test_step(self):
        """Tests the step function of the HeloModel class in bindings.py. This test checks that the
        step function correctly calls the StepH60 function in the C model."""
        helo = bindings.HeloModel()
        act = np.array([50.]*4)
        helo.step(act)


@pytest.mark.skip(reason="Requires compiled native model + wired-up bindings.py")
def test_reset_and_step():
    env = gym.make("HeloEnv-v0")
    obs, info = env.reset()
    assert env.observation_space.contains(obs)

    action = env.action_space.sample()
    obs, reward, terminated, truncated, info = env.step(action)
    assert env.observation_space.contains(obs)
    assert isinstance(reward, float)

