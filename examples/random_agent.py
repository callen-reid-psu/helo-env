"""Run a random agent against HeloEnv for a quick smoke test."""
import gymnasium as gym

import helo_env  # noqa: F401


def main() -> None:
    env = gym.make("HeloEnv-v0")
    obs, info = env.reset(seed=0)

    total_reward = 0.0
    for _ in range(200):
        action = env.action_space.sample()
        obs, reward, terminated, truncated, info = env.step(action)
        total_reward += reward
        if terminated or truncated:
            obs, info = env.reset()

    print(f"Total reward over rollout: {total_reward:.3f}")
    env.close()


if __name__ == "__main__":
    main()
